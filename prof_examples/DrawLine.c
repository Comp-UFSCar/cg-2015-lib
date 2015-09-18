

int DrawLine(point * p1, point * p2, window * win, bufferdevice * dev, int color) {
  float a, b;
  int i, j, aux;
  point * pn1, * pd1, * pn2, * pd2;
  
  pn1 = Sru2Srn(p1,win);
  pd1 = Srn2Srd(pn1,dev);
  pn2 = Sru2Srn(p2,win);
  pd2 = Srn2Srd(pn2,dev);
  
  if (pd1->x > pd2->x) {
    aux = pd1->x;
    pd1->x = pd2->x;
    pd2->x = aux;
    aux = pd1->y;
    pd1->y = pd2->y;
    pd2->y = aux;
    }

   i = pd1->x;
   j = pd1->y;
   
   if (pd1->x == pd2->x) {
     while (j < pd2->y) {
       dev->buffer[(dev->MaxY - j - 1) * dev->MaxX + i] = color;
       j++;
       }
     }
   else {
     a = (pd2->y - pd1->y)/(pd2->x - pd1->x);
     b = pd1->y - a*pd1->x;
     while (i < pd2->x) {
       dev->buffer[(dev->MaxY - j - 1) * dev->MaxX + i] = color;
       aux = j;
       j = round(a*(++i) + b);
       
       if (j > aux) {
	 while (aux < j) {
	   dev->buffer[(dev->MaxY - aux - 1) * dev->MaxX + i] = color; 
	   aux++;
	   }
         }
       if (j < aux) {
	 while (aux > j) { 
	   dev->buffer[(dev->MaxY - aux - 1) * dev->MaxX + i] = color;
	   aux--;
	   }
         }
        
       }
     }

  return 0;
  }


