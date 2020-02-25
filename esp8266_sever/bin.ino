
long getLength(int echo, int trig) {
  digitalWrite(echo, 0);
  delayMicroseconds(2);
  digitalWrite(echo, 1);
  delayMicroseconds(5);
  digitalWrite(echo, 0);
  duration = pulseIn(trig, 1);
  cm = microsecondsToCentimeters(duration);
 
  return cm;
}
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
