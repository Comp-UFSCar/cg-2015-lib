
object * CreateCircle(float radius, int color) {
  object * sphere;
  float x, y, th;
  int i;
  
  sphere = CreateObject(36);

  th = 0.0;
  for(i=0;i<10;i++) {
    x = radius*cos(th);
    y = sqrt(radius*radius - x*x);
    SetObject(SetPoint(x,y,color),sphere);
    th+=(10.0*PI)/180;
    } 
  for(i=10-1;i>=0;i--) {
    SetObject(SetPoint((-1.0)*sphere->points[i].x,sphere->points[i].y,color),sphere);  
    }  
  for(i=19-1;i>=9;i--) {
    SetObject(SetPoint(sphere->points[i].x,(-1.0)*sphere->points[i].y,color),sphere);  
    }
  for(i=28-1;i>=18;i--) {
    SetObject(SetPoint((-1.0)*sphere->points[i].x,sphere->points[i].y,color),sphere);  
    }
    
  return sphere;
  }


