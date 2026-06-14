# SCOPE: RAYTRACER

## v1 — In One Weekend

- [ ] `vec3` class with operator overloading
- [ ] `ray` class (origin, direction)
- [ ] `hittable` abstract base + `sphere` primitive
- [ ] `material` base: lambertian diffuse, metal, dielectric (glass)
- [ ] `camera` with configurable FOV, position, look-at
- [ ] Antialiasing via random sub-pixel sampling
- [ ] Scene: ground plane + random sphere forest (reference cover image)
- [ ] PPM output, then PNG via stb_image_write

## v2 — The Next Week

- [ ] BVH (bounding volume hierarchy) acceleration structure
- [ ] Motion blur (rays sampled over time)
- [ ] Textures: checkerboard, image texture mapping
- [ ] Perlin noise for procedural marble/wood
- [ ] Rectangles and boxes (axis-aligned)
- [ ] Volumes / fog (constant medium)
- [ ] Scene abstraction: list of objects + shared materials

## v3 — The Rest of Your Life

- [ ] Lights (area lights, direct lighting sampling)
- [ ] Importance sampling for faster convergence
- [ ] PDF / mixture sampling
- [ ] Triangles and mesh loading (OBJ)
- [ ] Thread pool rendering (OpenMP / std::thread)
- [ ] Scene files (JSON or custom DSL) for declarative scenes

## Architecture

```
raytracer/
├── src/
│   ├── main.cpp         # CLI, scene setup, render loop
│   ├── vec3.h           # 3D vector math
│   ├── ray.h            # ray definition
│   ├── hittable.h       # abstract hittable, hit_record
│   ├── sphere.h/cpp     # sphere primitive
│   ├── bvh.h/cpp        # BVH node (v2)
│   ├── material.h/cpp   # lambertian, metal, dielectric, light
│   ├── texture.h/cpp    # solid, checker, image, noise (v2)
│   ├── camera.h/cpp     # camera + ray generation
│   └── scene.h/cpp      # object list + render dispatch
├── external/
│   └── stb_image_write.h
├── scenes/              # scene presets
├── build/               # CMake out-of-source
└── CMakeLists.txt
```

### Key Design Decisions

- **Value semantics**: `vec3` is a plain struct, copied freely. No heap allocation in the hot loop.
- **Recursive rays**: `scatter()` returns attenuation + scattered ray. Terminated by depth or Russian roulette (v3).
- **BVH splits**: SAH (surface area heuristic) optional; median split for simplicity in v2.

## Milestones

| Day | Target |
|-----|--------|
| 1 | First image: gradient / first sphere |
| 3 | Materials: diffuse, metal, glass, fuzzy metal |
| 7 | BVH acceleration + scene with 100+ objects |
| 14 | Final scene: cover image quality, PNG export |

## Deferred / Future

- GPU ray tracing (CUDA / OptiX / Vulkan RT)
- Spectral rendering
- Denoising (OIDN / custom)
- Real-time preview (OpenGL rasterized fallback)
