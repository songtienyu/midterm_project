#include <iostream>
#include <cmath>

using namespace std;

double RiskCal(double Xi, double Yi, int RiskCnt, int RiskX[], int RiskY[], int RiskR[], int RiskP[]);
double AllRisk(double& FragDistance, int Ini_Xs, int Ini_Ys, int Ini_Xt, int Ini_Yt, \
int Xs, int Ys, int Xt, int Yt, int RiskCnt, int RiskX[], int RiskY[], int RiskR[], int RiskP[], int& tpX, int& tpY);



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
	
	int x1, x2, y1, y2, tpX, tpY, wX, wY;
	double F = 0, t_allrisk = 0, Zero = 0, allrisk = 0;
	double& Frag = F;//call by reference

	cout << endl << "輸入兩個轉折點的座標(x1 y1 x2 y2)：";
	cin >>  x1 >> y1 >> x2 >> y2;	
	allrisk = AllRisk(F, Xs, Ys, Xt, Yt, x1, y1, x2, y2, m, X, Y, R, P, tpX, tpY);
	cout << endl << "原本路段上AllRisk: " << allrisk << endl;
	cout << "-------------------------------" << endl;
	cout << "下一路段開頭未滿1公里距離: " << F << endl << endl; 

	t_allrisk = AllRisk(Zero, Xs, Ys, Xt, Yt, x1, y1, tpX, tpY, m, X, Y, R, P, wX, wY) + \
				AllRisk(F, Xs, Ys, Xt, Yt, tpX, tpY, x2, y2, m, X, Y, R, P, wX, wY);
				
	cout << endl << "在 (" << tpX << "," << tpY << ") 轉折的路段總風險：" << t_allrisk << endl;
	if (t_allrisk <= allrisk) cout << "風險較原本路徑小－－為較優路徑" << endl;
	else cout << "風險較原本路徑大－－為較差路徑" << endl;
	
    return 0;
}

double RiskCal(double Xi, double Yi, int RiskCnt, int RiskX[], int RiskY[], int RiskR[], int RiskP[])
{
	//計算單點風險 - songtien 
	
	int i = 0, j = 0;
	double risk = 0, d = 0, temp = 0;
	for(i = 0; i < RiskCnt; i++)
	{
		temp = (pow(Xi - RiskX[i], 2) + pow(Yi - RiskY[i], 2));
		d = sqrt(temp);
		if(d <= RiskR[i]) 
			risk = risk + RiskP[i] * ((RiskR[i] - d) / RiskR[i]);
		
	}
	return risk;
}

double AllRisk(double& FragDistance, int Ini_Xs, int Ini_Ys, int Ini_Xt, int Ini_Yt, \
							int Xs, int Ys, int Xt, int Yt, int RiskCnt, \
							int RiskX[], int RiskY[], int RiskR[], int RiskP[], int& tpX, int& tpY)
{
	
	//必須先傳入題目的起點終點!!!!!因為起始點終點都不計算風險!!!!! - songtien 

	double risk[1001] = {0}, risk_X[1001] = {0}, risk_Y[1001] = {0};
	double distance = 0, allrisk = 0, riskMax_X = 0, riskMax_Y = 0, Frag = 0, temp = 0;
	int j = 0, a = 0, i = 0, rec_i = 0, tpoint_X = 0, tpoint_Y = 0;
	
	distance = sqrt(pow(Xt-Xs, 2) + pow(Yt-Ys, 2));
	double d1 = ceil(distance - FragDistance);
	//要算有幾個點的距離，先減去開頭需要補足的部分 
	
	if (distance >= FragDistance)
	{
		if (Ini_Xs==Xs && Ini_Ys==Ys)//是起點 
		{
			risk_X[0] = Xs;
			risk_Y[0] = Ys;
			cout << "路段上起始座標: (" << risk_X[0] << "," << risk_Y[0] << ")" << endl;
			cout << "risk: " << risk[0] << endl << endl;
			for (j = 1; j < d1; j++)
        	{
        		if (risk_X[j]==Ini_Xt && risk_Y[j]==Ini_Yt) break;//若最後一個點座標是終點則不計算風險 
	            risk_X[j] = Xs + ((Xt - Xs) / distance) * j;
	            risk_Y[j] = Ys + ((Yt - Ys) / distance) * j;
	            cout << "路段上小風險點座標: (" << risk_X[j] << "," << risk_Y[j] << ")" << endl;
	         	risk[j] = RiskCal(risk_X[j], risk_Y[j], RiskCnt, RiskX, RiskY, RiskR, RiskP);
	         	cout << "risk: " << risk[j] << endl << endl;
	         	allrisk = allrisk + risk[j];
        	}
		}

		else//不是起點 
		{
			risk_X[0] = Xs + ((Xt - Xs) / distance) * FragDistance;
		    risk_Y[0] = Ys + ((Yt - Ys) / distance) * FragDistance;
		    cout << "路段上小風險點座標: (" << risk_X[0] << "," << risk_Y[0] << ")" << endl;
		    risk[0] = RiskCal(risk_X[0], risk_Y[0], RiskCnt, RiskX, RiskY, RiskR, RiskP);
		    cout << "risk: " << risk[0] << endl << endl;
		    allrisk = allrisk + risk[j];
		        
	        for (j = 1; j < d1; j++)
	        {
	        	if (risk_X[j]==Ini_Xt && risk_Y[j]==Ini_Yt) break;//若最後一個點座標是終點則不計算風險
		        risk_X[j] = Xs + ((Xt - Xs) / distance) * FragDistance + ((Xt - Xs) / distance) * j;
		    	risk_Y[j] = Ys + ((Yt - Ys) / distance) * FragDistance + ((Yt - Ys) / distance) * j;
		        cout << "路段上小風險點座標: (" << risk_X[j] << "," << risk_Y[j] << ")" << endl;
		        risk[j] = RiskCal(risk_X[j], risk_Y[j], RiskCnt, RiskX, RiskY, RiskR, RiskP);
		        cout << "risk: " << risk[j] << endl << endl;
		        allrisk = allrisk + risk[j];
	        }
		}
	}
	
	//路段距離不足1公里情形
	else if (distance < 1)
	{
		risk_X[0] = Xs;
		risk_Y[0] = Ys;
		j = 0;
	}
	
	//記錄風險最大的座標點 
	for (i = 0; i < d1; i++) 
	{
		if (risk[i] >= temp) 
		{
			temp = risk[i];
			rec_i = i;
		}
	}
		
		riskMax_X = risk_X[rec_i];
		riskMax_Y = risk_Y[rec_i];
		cout << "＃最大風險點: (" << risk_X[rec_i] << "," << risk_Y[rec_i] << ")" << endl << endl;
		
		//方圓一公里的整數點存入陣列中 ***目前未用陣列，測試中*** 
		tpoint_X = ceil(riskMax_X - 1);
		tpoint_Y = floor(riskMax_Y + 1);
		
		//以Call by Reference回傳轉折點座標 
		tpX = tpoint_X;
		tpY = tpoint_Y;
		
		cout << "＃最後一個風險點座標: (" << risk_X[j-1] << "," << risk_Y[j-1] << ")" << endl;
		double Dx = double(Xt) - risk_X[j-1];
		double Dy = double(Yt) - risk_Y[j-1];
		double temp2 = 0, Left = 0;
		temp2 = pow(Dx,2) + pow(Dy,2);//多的不足一公里的距離 
		Frag = sqrt(temp2);
		Left = 1 - Frag;
		cout << "Frag: " << Frag << " ; Left: "<< Left << endl << endl;
		FragDistance = Left;
		//以Call by Reference回傳了剩餘的片段 
		
		cout << "allrisk: " << allrisk << endl; 
		cout << "===============================" << endl;
		
	return allrisk;
	
}


