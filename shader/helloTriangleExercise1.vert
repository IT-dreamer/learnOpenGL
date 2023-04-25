#version 330 core

layout(location = 0) in vec3 aPos;

out vec4 vary_color;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vary_color = vec4(aPos, 1.0f) * 0.5 + vec4(0.2902, 0.5529, 0.5569, 0.593);
}