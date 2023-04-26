//Libraries to include
#include <stdlib.h>
#include <stdio.h>
 
// Prototype of Function

void greeting(void);
int choice(void);
void input(double *rf, double *rl, double *vi);
void input_i_d(double *c, double *rl, double *vi, double *time);
void input_adder(double *rf, double *vadd, double*vi);
void input_suber(double *rf, double *r1, double *r2, double *rg, double *v1, double *v2);
void calvout_invert();
void calvout_noninvert();
double calvout_integrate();
double calvout_differentiator();
void calvout_adder();
void calvout_subtractor();
double calgain(double vo,double vi);
void gaini();
void output_gain(double gain);
void output_vout(double vo);
void exiting(void);

// global variable

double rf,rl,rg,r1,r2,vi,vo,v1,v2,vadd,c,time,gain;

/*
here :- rf            feedback resistor
        rl,rg,r1,r2   terminal resistors
        vi,v1,v2      input voltages
        v0            output voltage of the op-amp
        c             capacitance
        gain          gain of the op-amp
*/

//Main code
int main()
{
    repeat:
        system("cls");
        greeting();
        double vo;
        char reply;
        int user_choice=choice();
        system("cls");
        switch(user_choice)
        {
            case 1:
                printf("Enter inputs for INVERTING OP-AMPS\n\n");
                calvout_invert();
                break;
            case 2:    
                printf("Enter inputs for NON - INVERTING OP-AMPS\n\n");
                calvout_noninvert();
                break;
            case 3:
                printf("Enter inputs for INTEGRATING OP-AMPS\n\n");
                vo=calvout_integrate();
                output_vout(vo);
                break;
            case 4:
                printf("Enter inputs for DIFFERNTIATING OP-AMPS\n\n");
                vo=calvout_differentiator();
                output_vout(vo);
                break;
            case 5:
                printf("Enter inputs for INVERTING ADDER OP-AMPS\n\n");
                calvout_adder();
                break;
            case 6:
                printf("Enter inputs for SUBSTRACTING OP-AMPS\n\n");
                calvout_subtractor();
                break;
            case 7:
                printf("Enter inputs to calcultate GAIN\n\n");
                gaini();
                break;
            default:
                printf("\n");
        }
        printf("Do you want to try again (Y/N):");
        scanf(" %c",&reply);
        if (reply=='y' || reply=='Y')
        {
            goto repeat;
        }
        else
        {
            exiting();
            return 0;
        }
}

/*

------------------------Function definition------------------------

*/

//First Terminal Windows
void greeting(void)
{
    printf("******************************************************************\n");
    printf("*                       Output  Voltage                          *\n");
    printf("*                              &                                 *\n");
    printf("*                       Gain Calculator                          *\n");
    printf("******************************************************************\n");
    printf("\n\n\n");
    printf("Choose one among the following :\n");
    printf("1.Inverting Amplifier\n");
    printf("2.Non-Inverting Amplifier\n");
    printf("3.Integrator Amplifier\n");
    printf("4.Differentiator Amplifier\n");
    printf("5.Summing Amplifier \n");
    printf("6.Subtractor Amplifier\n");
    printf("7.Gain Calculator\n");
    printf("\n\n");
}

//Take the  choice of operation
int choice(void)
{
    int choice, num_scanned;
    ask_choice:
        printf("Please enter your choice: ");
        num_scanned = scanf("%i", &choice);
        if (num_scanned == 1 && choice > 0 && choice < 8)
        {
            return choice;
        }
        else
        {
            printf("!!! Invalid choice. Please try again. !!!\n");
            while (getchar() != '\n');   // Clears the input buffer
            goto ask_choice;
        }
}

/*

------------------------Input Functions------------------------

*/

//taking the input from user for inverting and non inverting
void input(double *rf, double *rl, double *vi)
{
    double rvf,rvl;
    ask_rf:
        printf("Enter Feedback Resistance (in ohms):");
        scanf("%lf", &rvf);
    if (rvf<0)
    {
        printf("Enter Valid resistance \n");
        goto ask_rf;
    }
    else
    {
        *rf=rvf;
    }
    ask_rl:
        printf("Enter Input Resistance (in ohms):");
        scanf("%lf",&rvl);
    if (rvl<0)
    {
        printf("Enter Valid resistance \n");
        goto ask_rl;
    }
    else
    {
        *rl=rvl;
    }
    printf("Enter Terminal Voltage (in volts):");
    scanf("%lf", vi);
}

//tak inputs for integrating and differentiator op-amps
void input_i_d(double *c, double *rl, double *vi, double *time)
{
    double cv,rvl,tv;
    ask_cv:
        printf("Enter Capacitance (in Farad):");
        scanf("%lf", &cv);
    if (cv<0)
    {
        printf("Enter Valid Capacitance \n");
        goto ask_cv;
    }
    else
    {
        *c=cv;
    }
    ask_rl:
        printf("Enter Input Resistance (in ohms):");
        scanf("%lf",&rvl);
    if (rvl<0)
    {
        printf("Enter Valid resistance \n");
        goto ask_rl;
    }
    else
    {
        *rl=rvl;
    }
    printf("Enter Terminal Voltage (in volts):");
    scanf("%lf", vi);
    ask_tv:
        printf("Enter Time (in seconds):");
        scanf("%lf", &tv);
    if (tv<0)
    {
        printf("Enter Valid Time \n");
        goto ask_tv;
    }
    else
    {
        *time=tv;
    }
}

//taking inputs for adder
void input_adder(double *rf, double *vadd, double*vi)
{
    int n;
    double rvf;
    ask_rf:
        printf("Enter Feedback Resistance (in ohms):");
        scanf("%lf", &rvf);
    if (rvf<0)
    {
        printf("Enter Valid resistance \n");
        goto ask_rf;
    }
    else
    {
        *rf=rvf;
    }
    ask_again:
        printf("Enter The No.of Input Terminals:");
        scanf("%d", &n);
        if (n <= 0) 
        {
            printf("Error: number of input terminals must be positive\n");
            goto ask_again;
        }
        else
        {
            double vin[n], ri[n];
            for (int i=0;i<n;i++)
            {
                printf("Enter Input Voltage (in volts) for input no. %i:",i+1);
                scanf(" %lf",&vin[i]);
                ask_res:
                    printf("Enter Input Resistance (in ohms) for input no. %i:",i+1);
                    scanf(" %lf",&ri[i]);
                    if(ri[i]<=0)
                    {
                        printf("Enter Valid resistance \n");
                        goto ask_res;
                    }
                *vadd += vin[i]/ri[i];
                *vi += vin[i];
            }
        }
}

//Taking input for subtractor
void input_suber(double *rf, double *r1, double *r2, double *rg, double *v1, double *v2)
{
    double rvf,rv1,rv2,rvg;
    ask_rf:
        printf("Enter Feedback Resistance (in ohms):");
        scanf("%lf", &rvf);
    if (rvf<0)
    {
        printf("Enter Valid resistance \n");
        goto ask_rf;
    }
    else
    {
        *rf=rvf;
    }
    ask_r1:
        printf("Enter Input Resistance connected to  Inverting Terminal(in ohms):");
        scanf("%lf", &rv1);
    if (rv1<0)
    {
        printf("Enter Valid resistance \n");
        goto ask_r1;
    }
    else
    {
        *r1=rv1;
    }
    ask_r2:
        printf("Enter Input Resistance connected to Non-Inverting Terminal(in ohms):");
        scanf("%lf", &rv2);
    if (rv2<0)
    {
        printf("Enter Valid resistance \n");
        goto ask_r2;
    }
    else
    {
        *r2=rv2;
    }
    ask_rg:
        printf("Enter Grounded Resistance connected to Non-Inverting Terminal(in ohms):");
        scanf("%lf", &rvg);
    if (rvg<0)
    {
        printf("Enter Valid resistance \n");
        goto ask_rg;
    }
    else
    {
        *rg=rvg;
    }
    printf("Enter Voltage connected to Inverting Terminal (in volts):");
    scanf("%lf", v1);
    printf("Enter Voltage connected to Non-Inverting Terminal(in volts):");
    scanf("%lf", v2);
}

//Taking input for gain calculator
void input_gain(double *vi, double *vo)
{
    printf("Enter Input Terminal Voltage (in volts):");
    scanf("%lf", vi);
    printf("Enter Output Terminal Voltage (in volts):");
    scanf("%lf", vo);
}

/*

------------------------calculating function------------------------

*/

// calculating output voltage of inverting amp
void calvout_invert()
{
    input( &rf,  &rl, &vi);
    double vo=0.0; 
    vo= -(rf / rl) * vi ;
    gain= calgain( vo, vi);
    output_vout(vo);
    output_gain(gain);
}

// calculating output voltage of non-inverting amp
void calvout_noninvert()
{
    input( &rf,  &rl, &vi);
    double vo=0.0;
    vo = vi * (1 + (rf / rl));
    gain= calgain( vo, vi);
    output_vout(vo);
    output_gain(gain);
}

//calculating output voltage of integrator
double calvout_integrate()
{
    input_i_d(&c, &rl, &vi, &time);
    //x=integrate(vi,t,n);
    double vo = 0.0;
    vo = -(vi*time)/(rl*c); //changes needed
    return vo;
}

//calculating output voltage of differentiator
double calvout_differentiator()
{
    input_i_d(&c, &rl, &vi, &time);
    double vo = 0.0; 
    vo = -(rl*c)*(vi/time);
    return vo;
}

//calculating output voltage of inverting adder
void calvout_adder()
{
    input_adder(&rf,&vadd,&vi);
    double vo=0.0;
    vo = -rf*vadd;
    output_vout(vo);
   
}

//calculating output voltage of substractor
void calvout_subtractor()
{
    input_suber(&rf, &r1, &r2, &rg, &v1, &v2);
    double vo =0.0;
    vo =(vi*(rg/(rg+r2))*(1+(rf/r1)))-((rf/r1)*v2);
    output_vout(vo);
}

//calculating gain for inverting and non-inverting op-amp
double calgain(double vo,double vi)
{
    if(vi==0)
    {
        printf("Gain is infinite\n");
        return 0;
    }
    else
    {
        double gain = vo/vi ;
        return gain;       
    }
}

//calculating gain 
void gaini()
{
    input_gain(&vi ,&vo);
    if(vi==0)
    {
        printf("Gain is infinite\n");
    }
    else
    {
        gain=vo/vi;
        output_gain(gain);
    }
}

//display only the gain 
void output_gain(double gain)
{
    printf("The gain is %lf\n",gain);
}


//display only the output voltage
void output_vout(double vo)
{
    printf("The Output Voltage: %lf\n",vo);
}

//Exiting code 
void exiting(void)
{
    printf("\n\n************************** Program Ends **************************\n\n");
}
 
/*
Steps 
-->Greet with a welcome screen which asks for which OP-Amps operation to perform
-->Take the input and the particular function 
-->Take the input accordingly for the gain to calculate
-->Perform the operation according to function called 
-->Print the output and ask if you need to perform the calculation again
--Note-- Every input should be checked if entered correctly
 */