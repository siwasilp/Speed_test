void get_data()
{
  u1 = getLength(echo1, trig1);
  u2 = getLength(echo2, trig2);

  if (millis() >= time_1 + INTERVAL_MESSAGE1) {
    time_1 += INTERVAL_MESSAGE1;
    print_time(time_1);
    count = count + dir;
  }
  
  if (u1 < 50) {
    dir = 1;
    xxx = 0;
    if (yyy == 1) {
      count = 0 ;
      yyy = 0 ;
    }
  }

  if (u2 < 50) {
    dir   = 0 ;
    xxx   = 1 ;
    yyy = 1 ;
  }

  if (xxx == 1) {
    if (count == 0) {}
    else
    {
      x = ( length_x / count) * (18.00 / 5.00);
      xxx = 0;
    }
  }
  Serial.print(" A : ");
  Serial.print(u1);
  Serial.print(" B : ");
  Serial.print(u2);
}
