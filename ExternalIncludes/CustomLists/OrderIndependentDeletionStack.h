#pragma once

#include "CommonVectorObject.h"

#include <vector>

template<class T>
class OrderIndependentDeletionStack
{
public:
	OrderIndependentDeletionStack(size_t initialCapacity)
	{
		_nextID = std::numeric_limits<IDType>::lowest();
		_vectorID = GetNextVectorID();

		if (initialCapacity != 0)
		{
			_list.reserve(initialCapacity);
			_deletedList.reserve(initialCapacity);
			_additionOrder.reserve(initialCapacity);
		}

		for (size_t i = 0; i < sizeof(_padding); i++)
			_padding[i] = 0;
	}

	~OrderIndependentDeletionStack()
	{

	}

	OrderIndependentDeletionStack(const OrderIndependentDeletionStack<T>&) noexcept = default;
	OrderIndependentDeletionStack(OrderIndependentDeletionStack<T>&&) noexcept = default;

	OrderIndependentDeletionStack& operator=(const OrderIndependentDeletionStack<T>&) noexcept = default;
	OrderIndependentDeletionStack& operator=(OrderIndependentDeletionStack<T>&&) noexcept = default;

	IDObject<T> AddUniqueObject(const T& value, size_t addOnReserve)
	{
		auto found = std::find(_list.cbegin(), _list.cend(), value);

		if (found != _list.cend())
		{
			return IDObject<T>(found->GetObjectID(), _vectorID);
		}
		else
		{
			if (!_deletedList.empty())
			{
				size_t pos = _deletedList.back();
				_list[pos].ReplaceValue(IDSubobject<T>(GetNextId()), value);
				_deletedList.pop_back();
				auto ID = _list[pos].GetObjectID();
				_additionOrder.push_back(ID);
				return IDObject<T>(ID, _vectorID);
			}
			else
			{
				CheckCapacity(addOnReserve);

				_list.emplace_back(IDSubobject<T>(GetNextId()), value);
				auto ID = _list.back().GetObjectID();
				_additionOrder.push_back(ID);
				return IDObject<T>(ID, _vectorID);
			}
		}
	}

	IDObject<T> AddUniqueObject(T&& value, size_t addOnReserve)
	{
		auto found = std::find(_list.cbegin(), _list.cend(), value);

		if (found != _list.cend())
		{
			return IDObject<T>(found->GetObjectID(), _vectorID);
		}
		else
		{
			if (!_deletedList.empty())
			{
				size_t pos = _deletedList.back();
				_list[pos].ReplaceValue(IDSubobject<T>(GetNextId()), std::move(value));
				_deletedList.pop_back();
				auto ID = _list[pos].GetObjectID();
				_additionOrder.push_back(ID);
				return IDObject<T>(ID, _vectorID);
			}
			else
			{
				CheckCapacity(addOnReserve);

				_list.emplace_back(IDSubobject<T>(GetNextId()), std::move(value));
				auto ID = _list.back().GetObjectID();
				_additionOrder.push_back(ID);
				return IDObject<T>(ID, _vectorID);
			}
		}
	}

	IDObject<T> AddObject(const T& value, size_t addOnReserve)
	{
		if (!_deletedList.empty())
		{
			size_t pos = _deletedList.back();
			_list[pos].ReplaceValue(IDSubobject<T>(GetNextId()), value);
			_deletedList.pop_back();
			auto ID = _list[pos].GetObjectID();
			_additionOrder.push_back(ID);
			return IDObject<T>(ID, _vectorID);
		}
		else
		{
			CheckCapacity(addOnReserve);

			_list.emplace_back(IDSubobject<T>(GetNextId()), value);
			auto ID = _list.back().GetObjectID();
			_additionOrder.push_back(ID);
			return IDObject<T>(ID, _vectorID);
		}
	}

	IDObject<T> AddObject(T&& value, size_t addOnReserve)
	{
		if (!_deletedList.empty())
		{
			size_t pos = _deletedList.back();
			_list[pos].ReplaceValue(IDSubobject<T>(GetNextId()), std::move(value));
			_deletedList.pop_back();
			auto ID = _list[pos].GetObjectID();
			_additionOrder.push_back(ID);
			return IDObject<T>(ID, _vectorID);
		}
		else
		{
			CheckCapacity(addOnReserve);

			_list.emplace_back(IDSubobject<T>(GetNextId()), std::move(value));
			auto ID = _list.back().GetObjectID();
			_additionOrder.push_back(ID);
			return IDObject<T>(ID, _vectorID);
		}
	}

	bool RemoveObject(IDObject<T> objectID, bool throwOnIDNotFound)
	{
		if (objectID.GetVectorID() != _vectorID)
			throw std::runtime_error("OrderIndependentDeletionStack RemoveObject Error: Program tried to user an ID from another instance of this list!");

		auto it = std::find(_list.begin(), _list.end(), objectID.GetObjectID());

		if (it == _list.cend())
		{
			if (throwOnIDNotFound)
				throw std::runtime_error("OrderIndependentDeletionStack: Program tried to delete a non-existent entry in a list!");
			else
				return false;
		}
		else
		{
			if (it->HasValue())
			{
				it->DeleteObject();
				_deletedList.push_back(static_cast<size_t>(std::distance(_list.begin(), it)));
			}

			auto orderIt = std::find(_additionOrder.begin(), _additionOrder.end(), objectID.GetObjectID());

			if (orderIt != _additionOrder.cend())
			{
				_additionOrder.erase(orderIt);
			}
			else if (throwOnIDNotFound)
			{
				throw std::runtime_error("OrderIndependentDeletionStack: Program tried to delete a non-existent entry in an additon order list!");
			}

			return true;
		}
	}

	size_t GetSize() const { return _list.size(); }
	size_t GetUsedSize() const { return _additionOrder.size(); }
	size_t GetCapacity() const { return _list.capacity(); }
	size_t GetUnusedCapacity() const { return GetCapacity() - GetSize(); }
	size_t GetUnusedAndDeletedCapacity() const { return GetCapacity() - GetUsedSize(); }

	void ShrinkToFit(size_t changeToCapacity, bool addToCapacity) noexcept(std::is_nothrow_move_constructible_v<T> || std::is_nothrow_copy_constructible_v<T>)
	{
		if (_deletedList.empty())
			return;

		_list.shrink_to_fit();

		std::vector<CommonVectorObject<T>> tempList;

		if (addToCapacity)
		{
			size_t fullres = GetUsedSize() + changeToCapacity;

			if (fullres < changeToCapacity)
				throw std::runtime_error("UnsortedList ShrinkToFit Error: reservation amount overflowed!");

			tempList.reserve(fullres);
		}
		else
		{
			size_t usedSize = GetUsedSize();
			if (changeToCapacity > usedSize)
			{
				tempList.reserve(changeToCapacity);
			}
			else
			{
				tempList.reserve(usedSize);
			}
		}

		for (auto& object : _list)
		{
			if (object.HasValue())
			{
				if constexpr (std::is_nothrow_move_constructible_v<T>)
				{
					tempList.push_back(std::move(object));
				}
				else
				{
					if constexpr (std::is_nothrow_copy_constructible_v<T>)
					{
						tempList.push_back(object);
					}
					else
					{
						if constexpr (std::is_move_constructible_v<T>)
						{
							tempList.push_back(std::move(object));
						}
						else
						{
							tempList.push_back(object);
						}
					}
				}
			}
		}

		_list = std::move(tempList);
		_deletedList.clear();
		_deletedList.shrink_to_fit();
		_deletedList.reserve(_list.capacity());

		_additionOrder.shrink_to_fit();
		_additionOrder.reserve(_list.capacity());
	}

	T& GetObject(size_t position)
	{
		if (position >= _additionOrder.size())
			throw std::runtime_error("OrderIndependentDeletionStack GetObject Error: Program tried to read data from outside the addition order list!");

		auto& ID = _additionOrder[(_additionOrder.size() - position) - 1];

		auto it = std::find(_list.begin(), _list.end(), ID);

		if (it != _list.cend())
		{
			return it->GetObject();
		}
		else
		{
			throw std::runtime_error("OrderIndependentDeletionStack GetObject Error: An ID from the addition list does not exist in the object list!");
		}
	}

	const T& GetConstObject(size_t position) const
	{
		if (position >= _additionOrder.size())
			throw std::runtime_error("OrderIndependentDeletionStack GetConstObject Error: Program tried to read data from outside the addition order list!");

		auto& ID = _additionOrder[(_additionOrder.size() - position) - 1];

		auto it = std::find(_list.begin(), _list.end(), ID);

		if (it != _list.cend())
		{
			return it->GetConstObject();
		}
		else
		{
			throw std::runtime_error("OrderIndependentDeletionStack GetConstObject Error: An ID from the addition list does not exist in the object list!");
		}
	}

	T GetObjectCopy(size_t position)
	{
		if (position >= _additionOrder.size())
			throw std::runtime_error("OrderIndependentDeletionStack GetObjectCopy Error: Program tried to read data from outside the addition order list!");

		auto& ID = _additionOrder[(_additionOrder.size() - position) - 1];

		auto it = std::find(_list.begin(), _list.end(), ID);

		if (it != _list.cend())
		{
			return it->GetObjectCopy();
		}
		else
		{
			throw std::runtime_error("OrderIndependentDeletionStack GetObjectCopy Error: An ID from the addition list does not exist in the object list!");
		}
	}

	void Reset(size_t capacityAfterReset)
	{
		_list.clear();
		_deletedList.clear();
		_additionOrder.clear();

		_list.shrink_to_fit();
		_deletedList.shrink_to_fit();
		_additionOrder.shrink_to_fit();

		_vectorID = GetNextVectorID();

		if (capacityAfterReset != 0)
		{
			_list.reserve(capacityAfterReset);
			_deletedList.reserve(capacityAfterReset);
			_additionOrder.reserve(capacityAfterReset);
		}
	}


private:
	IDType _nextID;
	IDType _vectorID;
	std::vector<CommonVectorObject<T>> _list;
	std::vector<size_t> _deletedList;
	std::vector<IDSubobject<T>> _additionOrder;
	char _padding[16 - (((sizeof(_additionOrder) * 3) + (sizeof(_nextID) << 1)) % 8)];

	static IDType _nextVectorID;

	static IDType GetNextVectorID()
	{
		if (_nextVectorID == std::numeric_limits<IDType>::max())
			throw std::runtime_error("OrderIndependentDeletionStack::GetNextVectorID Error: Vector ID overflow!");

		return _nextVectorID++;
	}

	IDType GetNextId()
	{
		IDType ret = _nextID;
		if (_nextID == std::numeric_limits<IDType>::max())
			throw std::runtime_error("OrderIndependentDeletionStack Error: Id system overflowed!");

		_nextID++;
		return ret;
	}

	void ReserveAdditional(size_t addToCapacity)
	{
		auto size = _list.capacity();

		_list.reserve(size + addToCapacity);
		_deletedList.reserve(size + addToCapacity);
		_additionOrder.reserve(size + addToCapacity);
	}

	void CheckCapacity(size_t addOnReserve)
	{
		if (_list.capacity() == _list.size())
		{
			if (addOnReserve == 0)
			{
				size_t capacity = _list.capacity();
				if (capacity != 0)
					ReserveAdditional(capacity);
				else
					ReserveAdditional(1);
			}
			else
			{
				ReserveAdditional(addOnReserve);
			}
		}
	}
};
