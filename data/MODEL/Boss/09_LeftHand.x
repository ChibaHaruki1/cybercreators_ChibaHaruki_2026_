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
 52;
 -0.11865;7.18252;-7.31352;,
 -0.11865;-8.03990;-7.31352;,
 -0.11865;-8.03990;7.31352;,
 -0.11865;7.18252;7.31349;,
 17.47273;7.18252;7.31349;,
 19.41406;-7.13555;7.31352;,
 19.41406;-7.13555;-7.31352;,
 17.47273;7.18252;-7.31352;,
 6.47125;7.18252;7.31349;,
 -0.11865;7.18252;7.31349;,
 -0.11865;-8.03990;7.31352;,
 5.03607;-8.03990;7.31352;,
 6.99300;-13.80097;7.31352;,
 8.36269;7.18252;7.31349;,
 5.03607;-8.03990;7.31352;,
 -0.11865;-8.03990;7.31352;,
 5.18847;-8.03990;-7.31352;,
 6.90108;-13.80097;-7.31349;,
 6.99300;-13.80097;7.31352;,
 5.18847;-8.03990;-7.31352;,
 -0.11865;-8.03990;-7.31352;,
 -0.11865;7.18252;-7.31352;,
 6.62368;7.18252;-7.31352;,
 8.27073;7.18252;-7.31352;,
 6.90108;-13.80097;-7.31349;,
 6.62368;7.18252;-7.31352;,
 -0.11865;7.18252;7.31349;,
 6.47125;7.18252;7.31349;,
 8.36269;7.18252;7.31349;,
 8.27073;7.18252;-7.31352;,
 11.68289;-14.29999;7.31352;,
 11.63777;7.18252;7.31349;,
 11.70217;-14.29999;-7.31349;,
 11.68289;-14.29999;7.31352;,
 11.65703;7.18252;-7.31352;,
 11.70217;-14.29999;-7.31349;,
 11.63777;7.18252;7.31349;,
 11.65703;7.18252;-7.31352;,
 14.59195;-13.66114;7.31352;,
 19.41406;-7.13555;7.31352;,
 17.47273;7.18252;7.31349;,
 14.54051;7.18252;7.31349;,
 14.70760;-13.66114;-7.31352;,
 19.41406;-7.13555;7.31352;,
 14.59195;-13.66114;7.31352;,
 14.65607;7.18252;-7.31352;,
 17.47273;7.18252;-7.31352;,
 19.41406;-7.13555;-7.31352;,
 14.70760;-13.66114;-7.31352;,
 14.54051;7.18252;7.31349;,
 17.47273;7.18252;7.31349;,
 14.65607;7.18252;-7.31352;;
 
 22;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;8,11,12,13;,
 4;14,15,1,16;,
 4;14,16,17,18;,
 4;19,20,21,22;,
 4;19,22,23,24;,
 4;25,0,26,27;,
 4;25,27,28,29;,
 4;30,31,13,12;,
 4;32,33,18,17;,
 4;34,35,24,23;,
 4;36,37,29,28;,
 4;38,39,40,41;,
 4;38,41,31,30;,
 4;42,6,43,44;,
 4;42,44,33,32;,
 4;45,46,47,48;,
 4;45,48,35,34;,
 4;49,50,7,51;,
 4;49,51,37,36;;
 
 MeshMaterialList {
  3;
  22;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Boss\\Red.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Boss\\silver.jpg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  20;
  -1.000000;0.000000;0.000000;,
  0.990933;0.134357;0.000000;,
  0.969423;-0.245391;0.001714;,
  0.000001;0.000001;1.000000;,
  -0.952879;-0.303346;-0.001921;,
  0.000004;-0.000001;-1.000000;,
  0.000001;0.000002;1.000000;,
  0.000000;-1.000000;0.000000;,
  0.000004;-0.000001;-1.000000;,
  -0.000000;0.000001;1.000000;,
  0.053987;-0.998541;0.000617;,
  -0.000003;-0.000001;-1.000000;,
  -0.000001;0.000002;1.000000;,
  0.545089;-0.838376;0.002216;,
  -0.000003;-0.000000;-1.000000;,
  0.000000;0.000002;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  -0.104594;-0.994515;0.000255;,
  -0.000001;0.000002;1.000000;;
  22;
  4;0,0,0,0;,
  4;1,2,2,1;,
  4;6,15,15,6;,
  4;6,6,3,3;,
  4;7,7,7,7;,
  4;4,4,4,4;,
  4;8,16,16,8;,
  4;8,8,5,5;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;9,9,3,3;,
  4;10,10,18,18;,
  4;11,11,5,5;,
  4;17,17,17,17;,
  4;12,19,19,12;,
  4;12,12,9,9;,
  4;13,2,2,13;,
  4;13,13,10,10;,
  4;14,16,16,14;,
  4;14,14,11,11;,
  4;17,17,17,17;,
  4;17,17,17,17;;
 }
 MeshTextureCoords {
  52;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.290460;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.291540;,
  1.000000;0.486930;,
  0.000000;0.482130;,
  0.000000;0.291540;,
  0.000000;0.000000;,
  1.000000;0.308060;,
  1.000000;0.489560;,
  0.000000;0.486930;,
  0.000000;0.308060;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.306980;,
  1.000000;0.484760;,
  0.000000;0.489560;,
  0.000000;0.306980;,
  1.000000;0.000000;,
  1.000000;0.290460;,
  1.000000;0.482130;,
  0.000000;0.484760;,
  1.000000;0.670870;,
  0.000000;0.668310;,
  1.000000;0.710140;,
  0.000000;0.670870;,
  1.000000;0.707580;,
  0.000000;0.710140;,
  1.000000;0.668310;,
  0.000000;0.707580;,
  1.000000;0.836240;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.833310;,
  1.000000;0.880990;,
  0.000000;1.000000;,
  0.000000;0.836240;,
  1.000000;0.878060;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.880990;,
  1.000000;0.833310;,
  1.000000;1.000000;,
  0.000000;0.878060;;
 }
}