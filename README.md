# RAYTRACER

> A CPU ray tracer built from scratch. One pixel at a time.

## What Is This?

A path-tracing renderer built from first principles. No OpenGL, no Vulkan, no game engines—just a framebuffer, a ray, and the rendering equation. The goal is to understand how light behaves by simulating it directly.

## Why Build It?

- **Fundamentals**: Every graphics engine is a layer on top of ray tracing. Start at the bottom.
- **Beautiful Results**: Even simple diffuse + metal + glass produces images that feel real.
- **Reference**: This project follows the structure of **Peter Shirley's "Ray Tracing in One Weekend"** series (books 1–3). The code is a ground-up rewrite for practice, not a copy.

## Stack

- **C++17**
- **CMake** — build system
- **stb_image_write** — PNG output (header-only)
- **PPM** — raw RGB output for early debugging

## How to Build

```bash
cd raytracer
mkdir build && cd build
cmake ..
cmake --build . -j
./raytracer > image.ppm
# or for PNG:
./raytracer --png output.png
```

## Sample Output

```
[image_placeholder: first_sphere.png]
[image_placeholder: glass_metal_scene.png]
```

## Output Format

| Flag | Description |
|------|-------------|
| `--ppm` | Raw PPM, stdout (default) |
| `--png FILE` | PNG via stb_image_write |
| `--width N` | Image width (default 400) |
| `--height N` | Image height (default 225) |
| `--samples N` | Samples per pixel (default 100) |
| `--depth N` | Max ray bounce depth (default 50) |

## License

MIT
