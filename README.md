# CPU RTX

## Description
This is my C++11 implementation of a CPU software raytracer that outputs PPM files.  
It is based off **Peter Shirley's** raytracing book series, available [here](http://www.realtimerendering.com/raytracing/ "FTP root to download PDF") for free.  
One of the goal is to try to implement something usable to get reference images for various physically-based stuff. As such I might use [PBRT](http://www.pbr-book.org/) for that. For now it is simple but it could become a more complicated path-tracer.

## Philosophy
This is me trying to write yet-another-raytracer with minimal dependencies.  
Although I try to make it compilable somewhere else, I don't plan on writting support for other platforms than Win32. You could probably write a makefile that compiles this pretty fast.

## Task list
### Following "RT In One Weekend" (sort of)
- [X] Output PPM files of any size and filename
- [X] Build a ray class
- [X] Create the main raytracing loop
- [X] Add background support
- [X] Make a ray-sphere intersection
  - [X] basic intersection
  - [X] normal computation
- [X] Re-factoring
  - [X] Put stuff into structs
  - [X] Generalize raytracing spheres
  - [X] Put some of the structs into separate files
  - [X] Decouple raytracing from writting files
- [X] Add very basic material support
  - [X] albedo (RGB)
- [X] Add a proper camera
- [X] Anti-aliasing/better sampling
  - [X] basic random
  - [X] uniform random
- [X] Ambient/Diffuse Lighting basics
- [X] Specular Lighting basics
- [X] Re-factoring
  - [X] Shading ray generation in the material
  - [X] Fix progress bar
  - [X] Move utility functions somewhere else
  - [X] General clean-up and documentation
- [X] Add plane primitive
- [X] Postionable camera
- [X] Depth-of-Field
- [ ] Improving performance and quality
  - [X] Add binary PPM support
  - [ ] Simple multi-threading
  - [ ] Try better noise?
  - [ ] Work on the "correctness" of the mathematical aspect of lighting
  - [ ] More robust values for camera (preferably with units?)
  - [ ] Improve recursive ray generation (early stop?)
- [ ] Refraction support
- [ ] Box primitive support
- [ ] Emissive object support
- [ ] Triangle primitive support
- [ ] Mesh loading
- [ ] Refactoring
  - [ ] Better handling of materials
  - [ ] Tidying utilities

### Side Tasks
- [ ] Generalization of per-pixel effect (aka pixel "shader")
  - [ ] use a lambda-typedef
- [ ] Build a cornel box
- [ ] Find a simple scene description/config format
  - [ ] json is a popular choice
  - [ ] Write a cornel box scene to test
  - [ ] Add terminal UI to input a test scene path before raytracing

## Result so far
    Resolution: 3840x2160
    Sample per-pixel: 32
    Rays per sample: 4
![4K render](_readme_src/output_uhd.png)