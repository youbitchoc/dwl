void fibonacci(Monitor *m, int s) {
	unsigned int i=0, n=0, nx, ny, nw, nh, gih=0, giv=0;
	Client *c;
	
	wl_list_for_each(c, &clients, link)
		if (VISIBLEON(c, m) && !c->isfloating && !c->isfullscreen)
			n++;
	if (n == 0)
		return;
	
//	gih = m->gappih;
//	giv = m->gappiv;

	nx = m->w.x;
	ny = 0;
	nw = m->w.width;
	nh = m->w.height + giv;
	
	wl_list_for_each(c, &clients, link)
		if (VISIBLEON(c, m) && !c->isfloating && !c->isfullscreen) {	
			if ((i % 2 && nh / 2 > giv * c->bw)
			   || (!(i % 2) && nw / 2 > gih * c->bw)) {
				if (i < n - 1) {
					if (i % 2)
						nh /= 2;
					else
						nw /= 2;
					if (!s) {
						if ((i % 4) == 2)
							nx += nw;
						else if ((i % 4) == 3)
							ny += nh;
					}
				}

				switch (i % 4) {
					case 3:
						if (!s) {
							nx -= nw;
							break;
						}
					/* fallthrough */
					case 1:
						nx += nw;
						break;
					case 0:
						if (!s) {
							ny -= nh;
							break;
						}
					/* fallthrough */
					case 2:
						ny += nh;
						break;
				}
				if (i == 0) {
					if (n != 1)
						nw = m->w.width * m->mfact + gih/2;
					ny = m->w.y;
				}
				else if (i == 1)
					nw = m->w.width - nw + gih;
				i++;
			}
		resize(c, (struct wlr_box){ .x = nx, .y = ny, .width = nw - gih, .height = nh - giv}, 0);
		}
}

void
dwindle(Monitor *m) {
	fibonacci(m, 1);
}

void
spiral(Monitor *m) {
	fibonacci(m, 0);
}
