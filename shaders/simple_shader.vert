#version 450

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;

layout(location = 0) out vec3 fragColor;

layout(push_constant) uniform Push {
  mat3 transform;
  vec3 color;
} push;

void main() {
  // 1. Calculate the 2D transformed position (vec3 result)
  vec3 transformedPos = push.transform * vec3(position, 1.0);
  
  // 2. Assign to gl_Position as a vec4:
  //    - X and Y from the 2D transformation
  //    - Z is set to 0.0 (or 1.0)
  //    - W is set to 1.0 (for homogeneous coordinates)
  gl_Position = vec4(transformedPos.xy, 0.0, 1.0);
  
  // Use the color from the vertex attribute
  fragColor = color; 
  
  // If you wanted to use the push constant color instead:
  // fragColor = push.color;
}
