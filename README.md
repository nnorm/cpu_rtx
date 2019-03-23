# CPU RTX

## Description
This is my C++11 implementation of a CPU software raytracer that outputs PPM files.  
It is based off **Peter Shirley's** raytracing book series, available [here](http://www.realtimerendering.com/raytracing/ "FTP root to download PDF") for free.  
One of the goal is to try to implement something usable to get reference images for various physically-based stuff. As such I might use [PBRT](http://www.pbr-book.org/) for that. For now it is simple but it could become a more complicated path-tracer.

## Philosophy
This is me trying to write yet-another-raytracer with minimal dependencies.  
Although I try to make it compilable somewhere else, I don't plan on writting support for other platforms than Win32. You could probably write a makefile that compiles this pretty fast.

## Task list
### Following "RT In One Weekend"
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
- [ ] Improving performance and quality
- [ ] Re-factoring
- [ ] Depth-of-Field

### Side Tasks
- [ ] Manually build a cornel box
- [ ] Find a simple scene description language
  - [ ] Define syntax
  - [ ] Write parser
  - [ ] Write a cornel box scene to test
  - [ ] Add terminal UI to input a test scene path before raytracing
- [ ] Make a ray-box intersection
  - [ ] Add description language support
  - [ ] Add a box to the test scene