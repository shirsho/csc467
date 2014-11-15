{
	const int a = 1;
	int b = a;
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
