#include <iostream>
#include<cmath>

using namespace std;

double RiskCal(double Xi, double Yi, int RiskCnt, int RiskX[], int RiskY[], int RiskR[], int RiskP[]);
double AllRisk(double& FragDistance, int Ini_Xs, int Ini_Ys, int Ini_Xt, int Ini_Yt, int Xs, int Ys, int Xt, int Yt, int RiskCnt, int RiskX[], int RiskY[], int RiskR[], int RiskP[]);




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
    cout << endl << endl;
    /************/

	//路段allrisk函數測試 

	//riskcalculate test - songtien	
	int x1, x2, y1, y2;
	double F = 0;
	double& Frag = F;//call by reference

	cout << endl << "輸入兩個轉折點的座標(x1 y1 x2 y2)：";
	cin >>  x1 >> y1 >> x2 >> y2;	
	cout << endl << "路段上AllRisk: " << AllRisk(F, Xs, Ys, Xt, Yt, x1, y1, x2, y2, m, X, Y, R, P) << endl;
	cout << "下一路段開頭未滿1公里距離: " << F << endl; 
    return 0;
}

double RiskCal(double Xi, double Yi, int RiskCnt, int RiskX[], int RiskY[], int RiskR[], int RiskP[])
{//計算單點風險 - songtien 
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
			cout << "有風險的d: " << d << " risk: " << RiskP[i] * ((RiskR[i] - d) / RiskR[i]) << endl;
		}
	}
	return risk;
}

double AllRisk(double& FragDistance, int Ini_Xs, int Ini_Ys, int Ini_Xt, int Ini_Yt, int Xs, int Ys, int Xt, int Yt, int RiskCnt, int RiskX[], int RiskY[], int RiskR[], int RiskP[])
{//必須先傳入題目的起點終點!!!!!因為起始點終點都不計算風險!!!!! - songtien 
	double distance = 0, allrisk = 0, risk = 0, risk_X[1001] = {0}, risk_Y[1001] = {0}, Frag = 0;
	int j = 0, a = 0;
	distance = sqrt(pow(Xt-Xs, 2) + pow(Yt-Ys, 2));
//	cout << "distance:" << distance << endl;
	
		double d1 = ceil(distance - FragDistance);//要算有幾個點的距離，先減去開頭需要補足的部分 
		
		if (Ini_Xs==Xs && Ini_Ys==Ys)//是起點 
		{
			for (j = 1; j < d1; j++)
        	{
        		if (risk_X[j]==Ini_Xt && risk_Y[j]==Ini_Yt) break;//若最後一個點座標是終點則不計算風險 
	            risk_X[j] = Xs + ((Xt - Xs) / distance) * j;
	            risk_Y[j] = Ys + ((Yt - Ys) / distance) * j;
	            cout << "路段上小風險點座標: (" << risk_X[j] << "," << risk_Y[j] << ")" << endl;
	         	risk = RiskCal(risk_X[j], risk_Y[j], RiskCnt, RiskX, RiskY, RiskR, RiskP);
	         	cout << "risk: " << risk << endl << endl;
	         	allrisk = allrisk + risk;
        	}
		}

		else//不是起點 
		{
			risk_X[0] = Xs + ((Xt - Xs) / distance) * FragDistance;
		    risk_Y[0] = Ys + ((Yt - Ys) / distance) * FragDistance;
		    cout << "(" << risk_X[0] << "," << risk_Y[0] << ")" << endl;
		    risk = RiskCal(risk_X[0], risk_Y[0], RiskCnt, RiskX, RiskY, RiskR, RiskP);
		    cout << "risk: " << risk << endl << endl;
		    allrisk = allrisk + risk;
		        
	        for (j = 1; j < d1; j++)
	        {
	        	if (risk_X[j]==Ini_Xt && risk_Y[j]==Ini_Yt) break;
		        risk_X[j] = Xs + ((Xt - Xs) / distance) * j;
		    	risk_Y[j] = Ys + ((Yt - Ys) / distance) * j;
		        cout << "路段上小風險點座標: (" << risk_X[j-1] << "," << risk_Y[j-1] << ")" << endl;
		        risk = RiskCal(risk_X[j-1], risk_Y[j-1], RiskCnt, RiskX, RiskY, RiskR, RiskP);
		        cout << "risk: " << risk << endl << endl;
		        allrisk = allrisk + risk;
	        }
		}
		
		double Dx = Xt - risk_X[j-1];
		double Dy = Xt - risk_Y[j-1];
		Frag = sqrt(pow(Dx, 2) + pow(Dy, 2));//多的不足一公里的距離 
		cout << "Frag: " << Frag << " ; Left: "<< 1 - Frag << endl;
		FragDistance = 1 - Frag;//回傳了剩餘的片段 
	return allrisk;
}


