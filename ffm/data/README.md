# Free Form Map Data

What it sounds like

Three major files
- .ffmc (Free form map chunk)
- .ffmf (Free form map file)
- .ffmfd (Free form map file data (Helper file))

Chunks have vertices, lines, objects (like grass, rocks, etc), monsters, and an image

The image isn't stored in the .ffmc file (possibly a later thing todo), make an image with the same name as the chunk and place it in the same location (the name is just the chunk's coordinate on the map)

The free form map file just has a bunch of chunks

The free form map file data helper is what the Data::Types::Map uses, since loading all the chunks into RAM is not a good idea since it's already on the disk
