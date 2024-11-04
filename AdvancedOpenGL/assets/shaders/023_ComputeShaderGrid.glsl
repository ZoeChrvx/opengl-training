#version 450

// We will draw patches of 16*16 pixels, 80*45 times for a final 1280*720 image
layout(local_size_x = 16, local_size_y = 16) in;

// No data input: the compute shader will create the image output.
layout(rgba32f, binding = 0) uniform image2D img_output;

void main() {
    // gl_LocalInvocationID.xy * gl_WorkGroupID.xy == gl_GlobalInvocationID
    ivec2 coords = ivec2(gl_GlobalInvocationID);

    // We want to draw an orange and blue grid
    vec4 pixel;

    // Red alternance: when workgroup x is even we want workgroup y to be odd, and vice-versa
    if (mod(gl_WorkGroupID.x + gl_WorkGroupID.y, 4) == 0)
    {
        pixel = vec4(0.22, 0.47, 0.18, 1.0);
    }
    // Green alternance in case orange condition is not met
    else if (mod(gl_WorkGroupID.x + gl_WorkGroupID.y, 4) == 1)
    {
        pixel = vec4(0.98, 0.89, 0.52, 1.0);
    }
    // Blue
    else if (mod(gl_WorkGroupID.x + gl_WorkGroupID.y, 4) == 2)
    {
        pixel = vec4(0.39, 0.92, 0.57, 1.0);
    }
    // White
    else if (mod(gl_WorkGroupID.x + gl_WorkGroupID.y, 4) == 3)
    {
        pixel = vec4(1.0, 1.0, 1.0, 1.0);
    }
    imageStore(img_output, coords, pixel);
}