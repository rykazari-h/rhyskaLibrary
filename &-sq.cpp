	for(auto&[x,y]:s)for(auto&[sx,sy]:s)if(x!=sx||y!=sy){
		int dx=sx-x,dy=sy-y;
		int res=dx*dx+dy*dy;
		if((e(make_pair(x-dy,y+dx))&&e(make_pair(sx-dy,sy+dx)))||(e(make_pair(x+dy,y-dx))&&e(make_pair(sx+dy,sy-dx))))ans=max(ans,res);
	}
