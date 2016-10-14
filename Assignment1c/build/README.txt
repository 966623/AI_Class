pumpkin.txt produces a textured pumpkin that is smooth shaded wearing a textured flat shaded hat.
pumpkin_parallel.txt does the same but in parallel projection.
globe.txt produces a textured sphere and an untextured stand that has both smooth and flat shading. 

IMPLEMENTATION NOTE: Polygons do not cast shadows on objects they face away from. This was to avoid some 'terminator problem' related issues, which cause harsh shadows at edges of smooth shaded polygons due to the calculated smoothed normal not matching the actual normal of the polygon.