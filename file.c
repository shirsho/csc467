{
	vec4 red = gl_FragColor;
	vec4 blue = vec4(1.0,0.0,0.0,1.0);
	float a = dp3(red, blue);
	float b = a;
	if(true){
		if(true){
			b = rsq(a);
		}else{
			b = 1.0;
		}
	}
}


/*{
	vec4 fCol = gl_Color;
	vec4 fTex = gl_TexCoord;
	vec4 eyeNorm;
	vec4 coeff;
	vec4 shade;
	const vec4 lVec = env1; 
	const vec4 lHalf = gl_Light_Half; 
	const vec4 red = vec4(1.0,0.0,0.0,1.0);
	eyeNorm = fTex;
	eyeNorm[3] = dp3(eyeNorm,eyeNorm);
	eyeNorm[3] = rsq(eyeNorm[3]);
	eyeNorm = eyeNorm * eyeNorm[3];
	shade = gl_Light_Ambient * fCol;
	coeff[0] = dp3(lVec,eyeNorm);
	coeff[1] = dp3(lHalf,eyeNorm); 
	coeff[3] = gl_Material_Shininess[0];
	coeff = lit(coeff);
	shade = shade + coeff[1] * fCol;
	shade = shade + coeff[2] * fCol;
	gl_FragColor = shade;
}*/

/*

{
	vec4 temp;
	if (true){
		temp[0] = gl_Color[0] * gl_FragCoord[0];
		temp[1] = gl_Color[1] * gl_FragCoord[1];
		temp[2] = gl_Color[2];
		temp[3] = gl_Color[3] * gl_FragCoord[0] * gl_FragCoord[1];
	}
	else{
		temp = gl_Color;
	}
	gl_FragColor = temp;

}




	vec4 v4 = gl_Color;
	int num = gl_Color[3];

	gl_FragDepth = true;
	bool b = false;
	gl_FragDepth = b;
	vec4 v4 = vec4(1.0, 2.0, 3.0, 4.0);
	

	vec4 v = vec4(1,2,3,4);
	gl_FragCoord = v;

{ 
   vec4 temp;
if (true){
   temp[0] = gl_Color[0] * gl_FragCoord[0];
   temp[1] = gl_Color[1] * gl_FragCoord[1];
   temp[2] = gl_Color[2];
   temp[3] = gl_Color[3] * gl_FragCoord[0] * gl_FragCoord[1];
}
else{
   temp = gl_Color;
}
  gl_FragColor = temp;

}







/***********************
{	

	vec4 v = gl_Color;
	const int a = 1;
	int b = 2 + 2;
	
	{
		int c;
		c = a; 
		{
			int d;
			d = c;
			c = a;
		}
		{
			int e;
			e = a;
		}
	}
}
	*/
