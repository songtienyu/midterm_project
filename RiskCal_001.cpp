#include <iostream>
#include<cmath>

using namespace std;

double RiskCal(double Xi, double Yi, int RiskCnt, int RiskX[], int RiskY[], int RiskR[], int RiskP[]);
double AllRisk(int Ini_Xs, int Ini_Ys, int Ini_Xt, int Ini_Yt, int Xs, int Ys, int Xt, int Yt, int RiskCnt, int RiskX[], int RiskY[], int RiskR[], int RiskP[]);




int main()
{

    int n = 0, m = 0, w = 0, d = 0;
    cin >> n >> m >> w >> d;

    int* X = new int[m];
    int* Y = new int[m];
    int* R = new int[m];
    int* P = new int[m];
    int Xs = 0, Ys = 0, Xt = 0, Yt = 0;
    for(int i = 0; i < m; i++)
    {
        cin >> X[i];
    }
    for(int i = 0; i < m; i++)
    {
        cin >> Y[i];
    }
    for(int i = 0; i < m; i++)
    {
        cin >> R[i];
    }
    for(int i = 0; i < m; i++)
    {
        cin >> P[i];
    }
    cin >> Xs >> Ys >> Xt >> Yt;

    /*** test ***/
    cout << "< test >:" << endl;
    cout << n << " " << m << " " << w << " " << d << endl;
    for(int i = 0; i < m; i++)
    {
        cout << "Threat point " << i << ":\t("<< X[i] << "," << Y[i] << ")";
        cout << "\tRadius : " << R[i] << "\tpower :\t"  << P[i] << " " << endl;
    }
    cout << "Start: (" << Xs << "," << Ys << ")\tTerminal: (" << Xt << "," << Yt << ")" << endl;
    cout << "Next, Type below the number of turning points and each coordinates:" << endl;
    /************/

    int turn = 0;
    cin >> turn;
    int* turnX = new int[turn];
    int* turnY = new int[turn];
    for(int i = 0; i < turn; i++)
    {
        cin >> turnX[i] >> turnY[i];
    }

    /*** test ***/
    cout << "< test >:" << endl;
    cout << "turns = " << turn << endl;
    cout << "turning points: ";
    for(int i = 0; i < turn; i++)
        cout << "(" <<turnX[i] << "," <<  turnY[i] << ")";
    cout << endl;
    /************/


	double Xi = 0, Yi = 0;//*******************���I - songtien
	cin >> Xi >> Yi;
//	
//	//riskcalculate test - songtien
	cout << "RiskCal: " << RiskCal(Xi, Yi, m, X, Y, R, P);
	int x1, x2, y1, y2 = 0;	

	//allrisk
	cout << endl << "��J�������I���y��(x1 y1 x2 y2)�G";
	cin >>  x1 >> y1 >> x2 >> y2;
	cout << "AllRisk: " << AllRisk(Xs, Ys, Xt, Yt, x1, y1, x2, y2, m, X, Y, R, P);
	
    return 0;
}

double RiskCal(double Xi, double Yi, int RiskCnt, int RiskX[], int RiskY[], int RiskR[], int RiskP[])
{//�p����I���I - songtien 
	int i = 0, j = 0;
	double risk = 0, d = 0, temp = 0;
	for(i = 0; i < RiskCnt; i++)
	{
		temp = (pow(Xi - RiskX[i], 2) + pow(Yi - RiskY[i], 2));
		d = sqrt(temp);
		cout << "d: " << d << endl;
		//cout << "RiskPoint: (" << RiskX[i] << ", " << RiskY[i] << ")" << endl;
		if(d <= RiskR[i]) 
		{
			risk = risk + RiskP[i] * ((RiskR[i] - d) / RiskR[i]);
			cout << "�����I��d: " << d << " risk: " << RiskP[i] * ((RiskR[i] - d) / RiskR[i]) << endl;
		}
	}
	return risk;
}

double AllRisk(int Ini_Xs, int Ini_Ys, int Ini_Xt, int Ini_Yt, int Xs, int Ys, int Xt, int Yt, int RiskCnt, int RiskX[], int RiskY[], int RiskR[], int RiskP[])
{//�������ǤJ�D�ت��_�I���I!!!!!�]���_�l�I���I�����p�⭷�I!!!!! - songtien 
	double distance = 0, allrisk = 0, risk = 0, risk_X[1001] = {0}, risk_Y[1001] = {0};
	int j = 0, a = 0;
	distance = sqrt(pow(Xt-Xs, 2) + pow(Yt-Ys, 2));
	cout << "distance:" << distance << endl;
	
		double d1 = ceil(distance);
		
		if (Ini_Xs==Xs && Ini_Ys==Ys)//�O�_�I 
		{
			for (j = 1; j < d1; j++)
        	{
        		if (risk_X[j]==Ini_Xt && risk_Y[j]==Ini_Yt) break;//�Y�̫�@���I�y�ЬO���I�h���p�⭷�I 
	            risk_X[j] = Xs + ((Xt - Xs) / distance) * j;
	            risk_Y[j] = Ys + ((Yt - Ys) / distance) * j;
	            cout << "(" << risk_X[j] << "," << risk_Y[j] << ")" << endl;
	         	risk = RiskCal(risk_X[j], risk_Y[j], RiskCnt, RiskX, RiskY, RiskR, RiskP);
	         	cout << "risk: " << risk << endl << endl;
	         	allrisk = allrisk + risk;
        	}
		}

		else//���O�_�I 
		{
	        for (j = 1; j < d1; j++)
	        {
	        	if (risk_X[j]==Ini_Xt && risk_Y[j]==Ini_Yt) break;
		        risk_X[j-1] = Xs + ((Xt - Xs) / distance) * j;
		    	risk_Y[j-1] = Ys + ((Yt - Ys) / distance) * j;
		        cout << "(" << risk_X[j-1] << "," << risk_Y[j-1] << ")" << endl;
		        risk = RiskCal(risk_X[j-1], risk_Y[j-1], RiskCnt, RiskX, RiskY, RiskR, RiskP);
		        cout << "risk: " << risk << endl << endl;
		        allrisk = allrisk + risk;
	        }
		}
	return allrisk;
}



