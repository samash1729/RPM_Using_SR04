const int trigPin = 11; //Transmitter of Ultrasonic Sensor 
const int echoPin = 6; //Reciever of Ultrasonic Sensor
const int motorpin1 = 9; //To control direction of motor
const int motorpin2 = 10; //To control direction of motor
float t1,t2,RPM; //Defining Variables
long duration;
int distance;
void setup() //Setting Modes of Pins
{
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(motorpin1,OUTPUT);
  pinMode(motorpin2,OUTPUT);
  Serial.begin(9600);
}
void loop() 
{
    digitalWrite(motorpin1,HIGH); //Setting Particular Direction For The Motor To Turn In
    digitalWrite(motorpin2,LOW);
    read();
    if(distance>100)//For Distances when pulse not passing through The hole
    {
      t1 = millis(); //Setting The First Point just After The hole passes through the sensor
      calculate();
    }

}
void read() //Function Defined To Calculate Distance Between Nearest Object
{
  digitalWrite(trigPin, LOW); //Setting Trigger Pin LOW initially as it necessary before each reading
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);//Setting it HIGH
  delayMicroseconds(10); //Doing it for 10 micrseconds to generate 8 pulses
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); //Used to detect reflected pulse using pulseIn function
  distance= duration*0.034/2; //Formula to calculate speed taking speed of sound = 340 m/s and it calculates distance in cm
}
void calculate() // Function To Calculate RPM
{
  while(distance>100) 
  {
    read();
    if(distance<100)
    {
      t2 = millis(); //Point where hole appears again
      break;
    }
  }
  RPM = (60000)/(t2-t1); //(t2-t1) gives us time difference in milliseconds for which the hole completes one circle
  if(RPM>100) //Check Condition To filter out Some bad readings
  {
    ;
  }
  else
  {
    Serial.print("RPM : ");
    Serial.println(RPM);
  }
  t2 = 0;//Setting t1 and t2 to 0 
  t1 = 0;
}


