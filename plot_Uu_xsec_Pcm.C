#include <string>
#include <fstream>
#include <iostream>
#include <TMath.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TLatex.h>
#include <TLine.h>
void plot_Uu_xsec_Pcm(void)
{
 TCanvas *Can = new TCanvas("c","u,U ->m,M",200,10,600,400);
 double xMin=5.000000E+01, xMax=1.400000E+04, yMin=1.801706E-07, yMax=1.739068E+00;
 char buff[2000];
 double  X0[200],dX0[200];
 for(int i=0;i<200;i++){ X0[i]=xMin+(i+0.5)*(xMax-xMin)/200; dX0[i]=(xMax-xMin)/3./200;}
 double Xtext = xMin+0.3*(xMax-xMin);
 double Ytext= yMax;
 Can->SetLogy();
 double dYtext=pow(yMax/yMin,0.055);
 TH1F *hr = Can->DrawFrame(xMin,yMin,xMax,yMax);
 hr->SetXTitle("P_cm (GeV)");
 hr->SetYTitle("v*sigma (pb)");
 hr->SetTitle("U u -> m M");
 double  Y0[200];
 FILE*f=fopen("plot_Uu_xsec_Pcm.tab","r");
 for(int i=0;i<200;)
 {
  fscanf(f,"%[^\n]%*c",buff);
  if(buff[0]!='#') {  sscanf(buff," %lf"  ,Y0+i); i++;    }
 }
 fclose(f);
 TLatex ltx;
 ltx.SetTextFont(42);
 ltx.SetTextSize(0.04);
int i0,i1;
   for(i0=0;!isfinite(Y0[i0]);i0++);
   for(i1=199;!isfinite(Y0[i1]);i1--);
   TGraph *gr0 = new TGraph (1+i1-i0,X0+i0,Y0+i0);
   gr0->SetLineColor(1);
   gr0->Draw("L");
 Can->Print("plot_Uu_xsec_Pcm.pdf");
}
