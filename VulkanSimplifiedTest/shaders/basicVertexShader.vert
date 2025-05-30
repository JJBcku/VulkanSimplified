#version 450

layout(location = 0) in vec4 inPos;
layout(location = 1) in vec4 inColor;

layout(location = 0) out vec4 outColor;

layout(set = 0, binding  = 0) uniform UniformBufferObject
{
	mat4 model;
	mat4 view;
	mat4 projection;
} ubo;

void main()
{
	gl_Position = ubo.projection * ubo.view * ubo.model * vec4(inPos.xy, 0.0, 1.0);
	outColor = inColor;
}
