{	
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