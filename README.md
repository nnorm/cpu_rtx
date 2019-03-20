# CPU RTX

## Description
This is my C++11 implementation of a CPU software raytracer that outputs PPM files.  
It is based off **Peter Shirley's** raytracing book series, available [here](http://www.realtimerendering.com/raytracing/ "FTP root to download PDF") for free.

## Philosophy
This is me trying to write yet-another-raytracer with minimal dependancies.

## Task list

- [X] Output PPM files of any size and filename
- [X] Build a simple vec3 class
- [X] Build a ray class
- [X] Create the main raytracing loop
- [X] Add background support
- [X] Make a ray-sphere intersection
- [ ] Add lighting support
- [ ] Make a ray-plane intersection
- [ ] Add very basic material support
  - [ ] albedo (RGB)
- [ ] Manually build a cornel box
- [ ] Find a simple scene description language
  - [ ] Define syntax
  - [ ] Write parser
  - [ ] Write a cornel box scene to test
  - [ ] Add terminal UI to input a test scene path before raytracing
- [ ] Make a ray-box intersection
  - [ ] Add description language support
  - [ ] Add a box to the test scene