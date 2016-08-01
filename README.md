# Clouds
Final year project on simulating clouds.

Currently not working due to issues including the freeglut library.
Most of the calculating performed in fyp\Builder.cpp (setting light colour, colouring the cloud from line 338)


INPUT

The input text file (input.txt) takes in the following parameters:

  numBlobs=   - The amount of individual billboards (producing a list of fyp\BlobS.cpp)
  
  maxradius=  - The maximum radius of those billboards (randomly generated up to this)
  
  density=    - Defines how much light passes through each billboard
  
  time=       - Defines the colour and position of the light
  
  skyLight=   - Boolean value for whether to run lightMetasSky()/lightMetasSkySimple() functions
