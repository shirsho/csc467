{

	vec4 temp;
	gl_FragCoord = vec4(1.0, 2.0, 3.0, 4.0);
	/*vec4 temp;*/
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


/*
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
