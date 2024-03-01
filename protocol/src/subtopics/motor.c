void MOTOR_KILL(const unsigned char* data)
{

}

void MOTOR_MOVE(const unsigned char* data)
{
    for (int i = 0; i < 7; i++) 
    {
        printf("%d", data[i]);
    }printf("\n");
}