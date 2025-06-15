#version 450

layout(location = 0) in vec2 inTexCoord;

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 1) uniform sampler2D texSampler;

void main()
{
	vec4 inColor = texture(texSampler, inTexCoord);
	vec3 transitionColor = vec3(inColor.rgb);
	transitionColor = (vec3(1.055) * pow(transitionColor, vec3(1.0/2.4))) - vec3(0.055);

	outColor = vec4(transitionColor, inColor.a);
}