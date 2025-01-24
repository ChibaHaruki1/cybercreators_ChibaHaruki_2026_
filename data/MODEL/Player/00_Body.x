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
 94;
 -15.05096;23.61058;20.00000;,
 15.05096;23.61058;20.00000;,
 15.05096;20.99896;-20.00000;,
 -15.05096;20.99896;-20.00000;,
 -15.05096;1.73420;-20.00000;,
 15.05096;1.73420;-20.00000;,
 15.05096;-1.74530;20.00000;,
 -15.05096;-1.74530;20.00000;,
 15.05096;14.78020;-24.95992;,
 15.05096;1.73420;-20.00000;,
 -15.05096;1.73420;-20.00000;,
 -15.05096;14.61390;-24.95992;,
 -15.05096;20.99896;-20.00000;,
 15.05096;20.99896;-20.00000;,
 15.05096;14.34272;25.41942;,
 15.05096;1.73420;-20.00000;,
 15.05096;14.78020;-24.95992;,
 15.05096;20.99896;-20.00000;,
 -15.05096;14.17642;25.41942;,
 -15.05096;-1.74530;20.00000;,
 15.05096;-1.74530;20.00000;,
 15.05096;14.34272;25.41942;,
 15.05096;23.61058;20.00000;,
 -15.05096;23.61058;20.00000;,
 -15.05096;14.61390;-24.95992;,
 -15.05096;1.73420;-20.00000;,
 -15.05096;14.17642;25.41942;,
 -15.05096;20.99896;-20.00000;,
 -13.90448;23.35300;-18.79704;,
 -7.98262;23.35300;-18.79704;,
 -7.98262;20.84662;-18.79704;,
 -13.90448;20.84662;-18.79704;,
 -7.98262;26.85250;20.01596;,
 -13.90448;26.85250;20.01596;,
 -13.90448;21.94202;20.01596;,
 -7.98262;21.94202;20.01596;,
 -7.98262;25.77084;-12.01296;,
 -7.98262;26.85250;20.01596;,
 -7.98262;21.94202;20.01596;,
 -7.98262;21.19780;-12.20760;,
 -7.98262;20.84662;-18.79704;,
 -7.98262;23.35300;-18.79704;,
 -13.90448;25.77084;-11.99266;,
 -13.90448;23.35300;-18.79704;,
 -13.90448;20.84662;-18.79704;,
 -13.90448;21.19780;-12.18730;,
 -13.90448;21.94202;20.01596;,
 -13.90448;26.85250;20.01596;,
 -7.98262;25.77084;-12.01296;,
 -7.98262;23.35300;-18.79704;,
 -13.90448;23.35300;-18.79704;,
 -13.90448;25.77084;-11.99266;,
 8.05124;23.35300;-18.79704;,
 13.97310;23.35300;-18.79704;,
 13.97310;20.84662;-18.79704;,
 8.05124;20.84662;-18.79704;,
 13.97310;26.85250;20.01596;,
 8.05124;26.85250;20.01596;,
 8.05124;21.94202;20.01596;,
 13.97310;21.94202;20.01596;,
 13.97310;25.77084;-12.01296;,
 13.97310;26.85250;20.01596;,
 13.97310;21.94202;20.01596;,
 13.97310;21.19780;-12.20760;,
 13.97310;20.84662;-18.79704;,
 13.97310;23.35300;-18.79704;,
 8.05124;25.77084;-11.99266;,
 8.05124;23.35300;-18.79704;,
 8.05124;20.84662;-18.79704;,
 8.05124;21.19780;-12.18730;,
 8.05124;21.94202;20.01596;,
 8.05124;26.85250;20.01596;,
 13.97310;25.77084;-12.01296;,
 13.97310;23.35300;-18.79704;,
 8.05124;23.35300;-18.79704;,
 8.05124;25.77084;-11.99266;,
 -8.11696;27.72714;17.17352;,
 8.24452;27.72714;17.17352;,
 8.24452;23.53778;17.17352;,
 -8.11696;23.53778;17.17352;,
 8.24452;27.72714;17.17352;,
 8.24452;27.72714;19.94820;,
 8.24452;23.53778;19.94820;,
 8.24452;23.53778;17.17352;,
 8.24452;27.72714;19.94820;,
 -8.11696;27.72714;19.94820;,
 -8.11696;23.53778;19.94820;,
 8.24452;23.53778;19.94820;,
 -8.11696;27.72714;19.94820;,
 -8.11696;27.72714;17.17352;,
 -8.11696;23.53778;17.17352;,
 -8.11696;23.53778;19.94820;,
 8.24452;27.72714;17.17352;,
 -8.11696;27.72714;17.17352;;
 
 31;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;8,11,12,13;,
 4;14,6,15,16;,
 4;14,16,17,1;,
 4;18,19,20,21;,
 4;18,21,22,23;,
 4;24,25,7,26;,
 4;24,26,0,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;36,39,40,41;,
 4;42,43,44,45;,
 4;42,45,46,47;,
 4;48,49,50,51;,
 4;48,51,47,37;,
 4;52,53,54,55;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;60,63,64,65;,
 4;66,67,68,69;,
 4;66,69,70,71;,
 4;72,73,74,75;,
 4;72,75,71,61;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;88,81,92,93;;
 
 MeshMaterialList {
  2;
  31;
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
   0.800000;0.659200;0.003200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.400000;0.329600;0.001600;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.400000;0.400000;0.400000;;
  }
 }
 MeshNormals {
  19;
  -0.000928;0.884873;-0.465831;,
  0.000000;-0.996238;-0.086660;,
  0.000000;0.997875;-0.065152;,
  -0.000410;0.150128;-0.988667;,
  1.000000;0.000000;0.000000;,
  -0.000271;0.099224;0.995065;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000982;-0.357371;-0.933962;,
  0.000882;-0.320730;0.947170;,
  -0.001376;0.501451;0.865185;,
  -0.000320;0.982412;-0.186728;,
  -0.000574;0.942122;-0.335270;,
  -0.000058;0.999430;-0.033763;,
  -0.000320;0.982412;-0.186728;,
  -0.000574;0.942122;-0.335270;,
  -0.000058;0.999430;-0.033763;,
  0.000000;1.000000;0.000000;;
  31;
  4;2,2,0,0;,
  4;1,1,1,1;,
  4;3,9,9,3;,
  4;3,3,0,0;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;5,10,10,5;,
  4;5,5,11,11;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;12,13,13,12;,
  4;12,12,14,14;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;15,16,16,15;,
  4;15,15,17,17;,
  4;6,6,6,6;,
  4;4,4,4,4;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;18,18,18,18;;
 }
 MeshTextureCoords {
  94;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.522480;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.536460;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.452870;,
  0.000000;1.000000;,
  0.000000;0.522480;,
  0.000000;0.000000;,
  1.000000;0.466850;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.452870;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.536460;,
  1.000000;1.000000;,
  0.000000;0.466850;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.230210;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.219740;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.768700;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.779160;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.769790;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.768700;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.230210;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.219740;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.768700;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.779160;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.769790;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.768700;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;;
 }
}