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
 82;
 0.10725;0.00072;0.00036;,
 0.10725;-0.12347;-0.12383;,
 0.10725;0.00072;-0.17527;,
 0.10725;-0.17491;0.00036;,
 0.10725;-0.12347;0.12455;,
 0.10725;0.00072;0.17600;,
 0.10725;0.12491;0.12455;,
 0.10725;0.17635;0.00036;,
 0.10725;0.12491;-0.12383;,
 0.10561;-0.13535;-0.13571;,
 0.10561;0.00072;-0.19207;,
 0.10561;-0.19172;0.00036;,
 0.10561;-0.13535;0.13644;,
 0.10561;0.00072;0.19280;,
 0.10561;0.13679;0.13644;,
 0.10561;0.19315;0.00036;,
 0.10561;0.13679;-0.13571;,
 0.10094;-0.14543;-0.14578;,
 0.10094;0.00072;-0.20632;,
 0.10094;-0.20596;0.00036;,
 0.10094;-0.14543;0.14651;,
 0.10094;0.00072;0.20704;,
 0.10094;0.14686;0.14651;,
 0.10094;0.20740;0.00036;,
 0.10094;0.14686;-0.14578;,
 0.09396;-0.15216;-0.15251;,
 0.09396;0.00072;-0.21584;,
 0.09396;-0.21548;0.00036;,
 0.09396;-0.15216;0.15324;,
 0.09396;0.00072;0.21656;,
 0.09396;0.15359;0.15324;,
 0.09396;0.21692;0.00036;,
 0.09396;0.15359;-0.15251;,
 0.08573;-0.15452;-0.15488;,
 0.08573;0.00072;-0.21918;,
 0.08573;-0.21882;0.00036;,
 0.08573;-0.15452;0.15560;,
 0.08573;0.00072;0.21990;,
 0.08573;0.15596;0.15560;,
 0.08573;0.22026;0.00036;,
 0.08573;0.15596;-0.15488;,
 -0.08642;-0.15452;-0.15488;,
 -0.08642;0.00072;-0.21918;,
 -0.08642;-0.21882;0.00036;,
 -0.08642;-0.15452;0.15560;,
 -0.08642;0.00072;0.21990;,
 -0.08642;0.15596;0.15560;,
 -0.08642;0.22026;0.00036;,
 -0.08642;0.15596;-0.15488;,
 -0.09465;-0.15216;-0.15251;,
 -0.09465;0.00072;-0.21584;,
 -0.09465;-0.21548;0.00036;,
 -0.09465;-0.15216;0.15324;,
 -0.09465;0.00072;0.21656;,
 -0.09465;0.15359;0.15324;,
 -0.09465;0.21692;0.00036;,
 -0.09465;0.15359;-0.15251;,
 -0.10163;-0.14543;-0.14578;,
 -0.10163;0.00072;-0.20632;,
 -0.10163;-0.20596;0.00036;,
 -0.10163;-0.14543;0.14651;,
 -0.10163;0.00072;0.20704;,
 -0.10163;0.14686;0.14651;,
 -0.10163;0.20740;0.00036;,
 -0.10163;0.14686;-0.14578;,
 -0.10629;-0.13535;-0.13571;,
 -0.10629;0.00072;-0.19207;,
 -0.10629;-0.19172;0.00036;,
 -0.10629;-0.13535;0.13644;,
 -0.10629;0.00072;0.19280;,
 -0.10629;0.13679;0.13644;,
 -0.10629;0.19315;0.00036;,
 -0.10629;0.13679;-0.13571;,
 -0.10793;-0.12347;-0.12383;,
 -0.10793;0.00072;-0.17527;,
 -0.10793;-0.17491;0.00036;,
 -0.10793;-0.12347;0.12455;,
 -0.10793;0.00072;0.17600;,
 -0.10793;0.12491;0.12455;,
 -0.10793;0.17635;0.00036;,
 -0.10793;0.12491;-0.12383;,
 -0.10793;0.00072;0.00036;;
 
 88;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;8,2,10,16;,
 4;10,9,17,18;,
 4;9,11,19,17;,
 4;11,12,20,19;,
 4;12,13,21,20;,
 4;13,14,22,21;,
 4;14,15,23,22;,
 4;15,16,24,23;,
 4;16,10,18,24;,
 4;18,17,25,26;,
 4;17,19,27,25;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,18,26,32;,
 4;26,25,33,34;,
 4;25,27,35,33;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,32,40,39;,
 4;32,26,34,40;,
 4;34,33,41,42;,
 4;33,35,43,41;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,40,48,47;,
 4;40,34,42,48;,
 4;42,41,49,50;,
 4;41,43,51,49;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 4;46,47,55,54;,
 4;47,48,56,55;,
 4;48,42,50,56;,
 4;50,49,57,58;,
 4;49,51,59,57;,
 4;51,52,60,59;,
 4;52,53,61,60;,
 4;53,54,62,61;,
 4;54,55,63,62;,
 4;55,56,64,63;,
 4;56,50,58,64;,
 4;58,57,65,66;,
 4;57,59,67,65;,
 4;59,60,68,67;,
 4;60,61,69,68;,
 4;61,62,70,69;,
 4;62,63,71,70;,
 4;63,64,72,71;,
 4;64,58,66,72;,
 4;66,65,73,74;,
 4;65,67,75,73;,
 4;67,68,76,75;,
 4;68,69,77,76;,
 4;69,70,78,77;,
 4;70,71,79,78;,
 4;71,72,80,79;,
 4;72,66,74,80;,
 3;74,73,81;,
 3;73,75,81;,
 3;75,76,81;,
 3;76,77,81;,
 3;77,78,81;,
 3;78,79,81;,
 3;79,80,81;,
 3;80,74,81;;
 
 MeshMaterialList {
  4;
  88;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
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
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.194400;0.194400;0.194400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.088000;0.088000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.580000;0.580000;0.580000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  82;
  1.000000;0.000000;0.000000;,
  0.998821;-0.000000;-0.048550;,
  0.998821;-0.034330;-0.034330;,
  0.998821;-0.048550;-0.000000;,
  0.998821;-0.034330;0.034330;,
  0.998821;-0.000000;0.048549;,
  0.998821;0.034329;0.034329;,
  0.998821;0.048549;-0.000000;,
  0.998821;0.034329;-0.034330;,
  0.978777;0.000001;-0.204926;,
  0.978778;-0.144902;-0.144903;,
  0.978778;-0.204923;0.000000;,
  0.978778;-0.144903;0.144905;,
  0.978777;0.000000;0.204928;,
  0.978777;0.144908;0.144907;,
  0.978776;0.204933;-0.000000;,
  0.978776;0.144909;-0.144908;,
  0.890227;-0.000000;-0.455516;,
  0.890226;-0.322100;-0.322101;,
  0.890227;-0.455517;-0.000000;,
  0.890228;-0.322097;0.322098;,
  0.890228;0.000000;0.455514;,
  0.890226;0.322102;0.322100;,
  0.890223;0.455526;0.000000;,
  0.890226;0.322103;-0.322099;,
  0.618931;-0.000003;-0.785446;,
  0.618911;-0.555406;-0.555404;,
  0.618904;-0.785466;-0.000001;,
  0.618909;-0.555405;0.555408;,
  0.618915;-0.000001;0.785458;,
  0.618933;0.555391;0.555395;,
  0.618945;0.785434;0.000000;,
  0.618942;0.555389;-0.555386;,
  0.192597;-0.000002;-0.981278;,
  0.192578;-0.693872;-0.693869;,
  0.192566;-0.981284;-0.000000;,
  0.192566;-0.693870;0.693876;,
  0.192571;-0.000002;0.981283;,
  0.192598;0.693864;0.693872;,
  0.192618;0.981274;0.000000;,
  0.192610;0.693867;-0.693866;,
  -0.192618;-0.000002;-0.981274;,
  -0.192599;-0.693870;-0.693866;,
  -0.192587;-0.981280;0.000000;,
  -0.192587;-0.693867;0.693873;,
  -0.192592;-0.000002;0.981279;,
  -0.192619;0.693862;0.693869;,
  -0.192639;0.981270;0.000000;,
  -0.192631;0.693864;-0.693863;,
  -0.618946;-0.000003;-0.785433;,
  -0.618932;-0.555393;-0.555394;,
  -0.618930;-0.785446;-0.000001;,
  -0.618930;-0.555392;0.555397;,
  -0.618931;-0.000001;0.785445;,
  -0.618949;0.555382;0.555386;,
  -0.618961;0.785422;0.000000;,
  -0.618958;0.555380;-0.555377;,
  -0.890227;0.000000;-0.455517;,
  -0.890229;-0.322096;-0.322098;,
  -0.890232;-0.455507;-0.000000;,
  -0.890231;-0.322092;0.322095;,
  -0.890228;0.000000;0.455515;,
  -0.890225;0.322103;0.322100;,
  -0.890222;0.455526;0.000000;,
  -0.890225;0.322104;-0.322100;,
  -0.978777;0.000001;-0.204926;,
  -0.978778;-0.144903;-0.144902;,
  -0.978778;-0.204925;0.000000;,
  -0.978778;-0.144904;0.144905;,
  -0.978777;0.000000;0.204927;,
  -0.978777;0.144908;0.144907;,
  -0.978776;0.204933;-0.000000;,
  -0.978776;0.144909;-0.144908;,
  -0.998821;-0.000000;-0.048550;,
  -0.998821;-0.034331;-0.034330;,
  -0.998821;-0.048551;-0.000000;,
  -0.998821;-0.034330;0.034330;,
  -0.998821;-0.000000;0.048548;,
  -0.998821;0.034328;0.034329;,
  -0.998821;0.048548;-0.000000;,
  -0.998821;0.034329;-0.034329;,
  -1.000000;0.000000;0.000000;;
  88;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,49,57,64;,
  4;57,58,66,65;,
  4;58,59,67,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,57,65,72;,
  4;65,66,74,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,65,73,80;,
  3;73,74,81;,
  3;74,75,81;,
  3;75,76,81;,
  3;76,77,81;,
  3;77,78,81;,
  3;78,79,81;,
  3;79,80,81;,
  3;80,73,81;;
 }
 MeshTextureCoords {
  82;
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
