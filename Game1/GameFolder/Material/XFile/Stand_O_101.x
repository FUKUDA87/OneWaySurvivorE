xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 58;
 0.00000;0.30187;-0.09036;,
 0.06389;0.30187;-0.06389;,
 0.06389;0.05567;-0.06389;,
 0.00000;0.05567;-0.09036;,
 0.09036;0.30187;0.00000;,
 0.09036;0.05567;0.00000;,
 0.06389;0.30187;0.06389;,
 0.06389;0.05567;0.06389;,
 0.00000;0.30187;0.09036;,
 0.00000;0.05567;0.09036;,
 -0.06389;0.30187;0.06389;,
 -0.06389;0.05567;0.06389;,
 -0.09036;0.30187;0.00000;,
 -0.09036;0.05567;0.00000;,
 -0.06389;0.30187;-0.06389;,
 -0.06389;0.05567;-0.06389;,
 0.00000;0.30187;-0.09036;,
 0.00000;0.05567;-0.09036;,
 0.00000;0.30187;0.00000;,
 0.00000;0.30187;0.00000;,
 0.00000;0.30187;0.00000;,
 0.00000;0.30187;0.00000;,
 0.00000;0.30187;0.00000;,
 0.00000;0.30187;0.00000;,
 0.00000;0.30187;0.00000;,
 0.00000;0.30187;0.00000;,
 0.00000;0.05567;0.00000;,
 0.00000;0.05567;0.00000;,
 0.00000;0.05567;0.00000;,
 0.00000;0.05567;0.00000;,
 0.00000;0.05567;0.00000;,
 0.00000;0.05567;0.00000;,
 0.00000;0.05567;0.00000;,
 0.00000;0.05567;0.00000;,
 -0.27952;0.07545;0.27952;,
 0.27952;0.07545;0.27952;,
 0.27952;0.07545;-0.27952;,
 -0.27952;0.07545;-0.27952;,
 0.27952;0.06324;0.29173;,
 -0.27952;0.06324;0.29173;,
 0.29173;0.06324;-0.27952;,
 0.29173;0.06324;0.27952;,
 -0.27952;0.06324;-0.29173;,
 0.27952;0.06324;-0.29173;,
 -0.29173;0.06324;0.27952;,
 -0.29173;0.06324;-0.27952;,
 0.27952;0.01795;-0.29173;,
 -0.27952;0.01795;-0.29173;,
 0.29173;0.01795;-0.27952;,
 -0.27952;0.00575;-0.27952;,
 0.27952;0.00575;-0.27952;,
 -0.29173;0.01795;-0.27952;,
 0.27952;0.00575;0.27952;,
 -0.27952;0.00575;0.27952;,
 0.29173;0.01795;0.27952;,
 -0.27952;0.01795;0.29173;,
 0.27952;0.01795;0.29173;,
 -0.29173;0.01795;0.27952;;
 
 50;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,1,0;,
 3;19,4,1;,
 3;20,6,4;,
 3;21,8,6;,
 3;22,10,8;,
 3;23,12,10;,
 3;24,14,12;,
 3;25,16,14;,
 3;26,3,2;,
 3;27,2,5;,
 3;28,5,7;,
 3;29,7,9;,
 3;30,9,11;,
 3;31,11,13;,
 3;32,13,15;,
 3;33,15,17;,
 4;34,35,36,37;,
 4;38,35,34,39;,
 4;40,36,35,41;,
 4;42,37,36,43;,
 4;44,34,37,45;,
 3;44,39,34;,
 3;38,41,35;,
 3;40,43,36;,
 3;42,45,37;,
 4;42,43,46,47;,
 4;48,46,43,40;,
 4;49,47,46,50;,
 4;45,42,47,51;,
 3;48,50,46;,
 3;49,51,47;,
 4;49,50,52,53;,
 4;54,52,50,48;,
 4;55,53,52,56;,
 4;51,49,53,57;,
 3;54,56,52;,
 3;55,57,53;,
 4;55,56,38,39;,
 4;41,38,56,54;,
 4;57,55,39,44;,
 4;41,54,48,40;,
 4;57,44,45,51;;
 
 MeshMaterialList {
  1;
  50;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.552157;0.000000;0.128627;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  34;
  0.000000;1.000000;0.000000;,
  -0.000007;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  -0.000007;0.000000;1.000000;,
  -0.707110;0.000000;0.707104;,
  -1.000000;0.000000;0.000000;,
  -0.707110;0.000000;-0.707104;,
  0.000000;-1.000000;-0.000000;,
  -0.367001;0.854763;0.367001;,
  0.367001;0.854763;0.367001;,
  0.367001;0.854763;-0.367001;,
  -0.367001;0.854763;-0.367001;,
  -0.367001;0.367001;-0.854763;,
  0.367001;0.367001;-0.854763;,
  0.367001;-0.367001;-0.854763;,
  -0.367001;-0.367001;-0.854763;,
  -0.367001;-0.854764;-0.367001;,
  0.367001;-0.854764;-0.367001;,
  0.367001;-0.854764;0.367001;,
  -0.367001;-0.854764;0.367001;,
  -0.367001;-0.367001;0.854763;,
  0.367001;-0.367001;0.854763;,
  0.367001;0.367001;0.854763;,
  -0.367001;0.367001;0.854763;,
  0.854763;0.367001;0.367001;,
  0.854763;-0.367001;0.367001;,
  0.854763;-0.367001;-0.367001;,
  0.854763;0.367001;-0.367001;,
  -0.854763;-0.367001;0.367001;,
  -0.854763;0.367001;0.367001;,
  -0.854763;0.367001;-0.367001;,
  -0.854763;-0.367001;-0.367001;;
  50;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;10,11,12,13;,
  4;24,11,10,25;,
  4;29,12,11,26;,
  4;14,13,12,15;,
  4;31,10,13,32;,
  3;31,25,10;,
  3;24,26,11;,
  3;29,15,12;,
  3;14,32,13;,
  4;14,15,16,17;,
  4;28,16,15,29;,
  4;18,17,16,19;,
  4;32,14,17,33;,
  3;28,19,16;,
  3;18,33,17;,
  4;18,19,20,21;,
  4;27,20,19,28;,
  4;22,21,20,23;,
  4;33,18,21,30;,
  3;27,23,20;,
  3;22,30,21;,
  4;22,23,24,25;,
  4;26,24,23,27;,
  4;30,22,25,31;,
  4;26,27,28,29;,
  4;30,31,32,33;;
 }
 MeshTextureCoords {
  58;
  0.000000;0.000000;
  0.125000;0.000000;
  0.125000;1.000000;
  0.000000;1.000000;
  0.250000;0.000000;
  0.250000;1.000000;
  0.375000;0.000000;
  0.375000;1.000000;
  0.500000;0.000000;
  0.500000;1.000000;
  0.625000;0.000000;
  0.625000;1.000000;
  0.750000;0.000000;
  0.750000;1.000000;
  0.875000;0.000000;
  0.875000;1.000000;
  1.000000;0.000000;
  1.000000;1.000000;
  0.062500;0.000000;
  0.187500;0.000000;
  0.312500;0.000000;
  0.437500;0.000000;
  0.562500;0.000000;
  0.687500;0.000000;
  0.812500;0.000000;
  0.937500;0.000000;
  0.062500;1.000000;
  0.187500;1.000000;
  0.312500;1.000000;
  0.437500;1.000000;
  0.562500;1.000000;
  0.687500;1.000000;
  0.812500;1.000000;
  0.937500;1.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;;
 }
}