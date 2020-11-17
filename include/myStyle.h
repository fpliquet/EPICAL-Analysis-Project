#ifndef MYSTYLE_H
#define MYSTYLE_H

#include "TStyle.h"
#include "TLatex.h"
#include "TLine.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TF1.h"
#include "TLegend.h"
#include "TString.h"
#include "TObjString.h"
#include "TObjArray.h"
#include "TCanvas.h"
#include <Riostream.h>

class myStyle {

	public:

		myStyle ();
		~myStyle ();

		void Loaded ();

		void ApplyStyle (TStyle *gStyle) {

			gStyle->SetCanvasDefW(1200);
			gStyle->SetCanvasDefH(800);

			gStyle->SetPadBottomMargin(0.10);
			gStyle->SetPadLeftMargin(0.10);
			gStyle->SetPadTopMargin(0.04);
			gStyle->SetPadRightMargin(0.015);

			gStyle->SetErrorX(0);

//			gStyle->SetOptStat(0);
//			gStyle->SetTitle("");

//			gStyle->SetTitleFont(textfont);
//			gStyle->SetTitleSize(textsize);
//			gStyle->SetTitleOffset(1.2,"Y");
//			gStyle->SetTitleOffset(1.1,"X");
//
//			gStyle->SetLabelFont(textfont,"X");
//			gStyle->SetLabelSize(textsize,"X");
//			gStyle->SetLabelFont(textfont,"Y");
//			gStyle->SetLabelSize(textsize,"Y");

//			gStyle->SetMarkerStyle(markerstyle);
//			gStyle->SetMarkerSize(markersize);

//			gStyle->SetLineWidth(2.0);

		}


		void makenicehist (TH1F *hist, const Char_t* xaxistitle, const Char_t* yaxistitle, Int_t color = kBlack) {

			hist->SetStats(0);
			hist->SetTitle("");

			hist->GetXaxis()->SetTitleFont(textfont);
			hist->GetXaxis()->SetTitleSize(textsize);
			hist->GetXaxis()->SetTitle(xaxistitle);

			hist->GetYaxis()->SetTitleFont(textfont);
			hist->GetYaxis()->SetTitleSize(textsize);
			hist->GetYaxis()->SetTitle(yaxistitle);

			hist->GetZaxis()->SetTitleFont(textfont);
			hist->GetZaxis()->SetTitleSize(textsize);
//			hist->GetZaxis()->SetTitle(zaxistitle);

			hist->SetTitleOffset(ytitleoffset,"Y");
			hist->SetTitleOffset(xtitleoffset,"X");

			hist->SetLabelFont(textfont,"X");
			hist->SetLabelSize(textsize,"X");
			hist->SetLabelFont(textfont,"Y");
			hist->SetLabelSize(textsize,"Y");
			hist->SetLabelFont(textfont,"Z");
			hist->SetLabelSize(textsize,"Z");

			hist->SetMarkerStyle(markerstyle);
			hist->SetMarkerSize(markersize);
			hist->SetMarkerColor(color);

			hist->SetLineColor(color);
			hist->SetLineWidth(linewidth);
			hist->SetLineStyle(linestyle);

		}


		void makenicegraph (TGraph *graph, const Char_t* xaxistitle, const Char_t* yaxistitle, Int_t color = kBlack) {

			graph->SetTitle("");

			graph->GetXaxis()->SetTitleFont(textfont);
			graph->GetXaxis()->SetTitleSize(textsize);
			graph->GetXaxis()->SetTitle(xaxistitle);

			graph->GetYaxis()->SetTitleFont(textfont);
			graph->GetYaxis()->SetTitleSize(textsize);
			graph->GetYaxis()->SetTitle(yaxistitle);

			graph->GetYaxis()->SetTitleOffset(ytitleoffset);
			graph->GetXaxis()->SetTitleOffset(xtitleoffset);

			graph->GetXaxis()->SetLabelFont(textfont);
			graph->GetXaxis()->SetLabelSize(textsize);
			graph->GetYaxis()->SetLabelFont(textfont);
			graph->GetYaxis()->SetLabelSize(textsize);

			graph->SetMarkerStyle(markerstyle);
			graph->SetMarkerSize(markersize);
			graph->SetMarkerColor(color);

			graph->SetLineColor(color);
			graph->SetLineWidth(linewidth);
			graph->SetLineStyle(linestyle);

			graph->SetFillColor(color);

		}


		void makenicefunction (TF1 *f, const Char_t* xaxistitle, const Char_t* yaxistitle, Int_t color = kBlack) {

			f->SetTitle(Form(";%s;%s", xaxistitle, yaxistitle));

			f->GetXaxis()->SetTitleFont(textfont);
			f->GetXaxis()->SetTitleSize(textsize);
			f->GetXaxis()->SetTitle(xaxistitle);

			f->GetYaxis()->SetTitleFont(textfont);
			f->GetYaxis()->SetTitleSize(textsize);
			f->GetYaxis()->SetTitle(yaxistitle);

			f->GetYaxis()->SetTitleOffset(ytitleoffset);
			f->GetXaxis()->SetTitleOffset(xtitleoffset);

			f->GetXaxis()->SetLabelFont(textfont);
			f->GetXaxis()->SetLabelSize(textsize);
			f->GetYaxis()->SetLabelFont(textfont);
			f->GetYaxis()->SetLabelSize(textsize);

			f->SetMarkerStyle(markerstyle);
			f->SetMarkerSize(markersize);
			f->SetMarkerColor(color);

			f->SetLineColor(color);
			f->SetLineWidth(linewidth);
			f->SetLineStyle(linestyle);

			f->SetFillColor(color);

		}


		void drawratio (TCanvas* canvas, TObjArray* oaHists) {

			canvas->cd();

			TPad *pad1 = new TPad("1pad1","1pad1",0,0.3,1,1);
//			pad1->SetLogy(kFALSE);
		    pad1->SetBottomMargin(0);
		    pad1->Draw();
		    TPad *pad2 = new TPad("1pad2","1pad2",0,0,1,0.3);
		    pad2->SetLogy(kFALSE);
		    pad2->SetTopMargin(0);
		    pad2->SetBottomMargin(0.27);
		    pad2->Draw();
//		    TPad *pad3 = new TPad("1pad3","1pad3",0,0,1,1);
//		    pad3->SetFillColorAlpha(kWhite,0.);
//		    pad3->Draw();

		    pad1->cd();
		    for (Int_t iEntry = 0; iEntry < oaHists->GetEntries(); iEntry++) {
		    	if (iEntry == 0) {
		    		((TH1F*) oaHists->At(iEntry))->SetTitleOffset(1.5,"Y");
		    		((TH1F*) oaHists->At(iEntry))->Draw("p");
		    	}
		    	else {((TH1F*) oaHists->At(iEntry))->Draw("p,same");}
		    }

		    pad2->cd();
		    for (Int_t iEntry = 1; iEntry < oaHists->GetEntries(); iEntry++) {
		    	TH1F* hRatioTemp = (TH1F*) ((TH1F*) oaHists->At(0))->Clone("hRatioTemp");
		    	hRatioTemp->GetYaxis()->SetTitle("ratio");

		    	if (oaHists->At(iEntry)->InheritsFrom(TH1::Class())) {hRatioTemp->Divide((TH1F*) oaHists->At(iEntry));}
		    	else if (oaHists->At(iEntry)->InheritsFrom(TF1::Class())) {hRatioTemp->Divide((TF1*) oaHists->At(iEntry));}
		    	else {
		    		printf(" ### Warning: Object is neither TH1F* nor TF1*!!! Cannot divide to get ratio! ### \n");
		    		continue;
		    	}

		    	if (iEntry == 1) {
		    		hRatioTemp->SetTitleOffset(4.,"X");
		    		hRatioTemp->Draw("p");
		    	}
		    	else {hRatioTemp->Draw("p,same");}
		    }
		    drawratioline(6.,30.);
		    pad1->cd();

		}


		void drawcollsysinfo (const Char_t* dataset, const Char_t* trigger = 0x0, const Char_t* ptrange = 0x0, Float_t newxpos = 0., Float_t newypos = 0.) {

			l.SetTextFont(textfont);
			l.SetTextSize(textsize);

			Float_t drawxpos = xpos;
			Float_t drawypos = ypos;

			if (newxpos) drawxpos = newxpos;
			if (newypos) drawypos = newypos;

			Int_t iLine = 0;

			if (bdrawalicelable) l.DrawLatexNDC(drawxpos,drawypos-iLine++*yspace,"ALICE Work in Progress");
			if (bdrawrxinfo) l.DrawLatexNDC(drawxpos,drawypos-iLine++*yspace,Form("%s #rightarrow #gamma#gamma",sAnalyzedParticle.Data())); // pN #rightarrow #etaX
			if (!sCollSysInfo.EqualTo("")) l.DrawLatexNDC(drawxpos,drawypos-iLine++*yspace,sCollSysInfo.Data()); // "p-Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV"
			// if (sCollSysInfo.Data() != "") l.DrawLatexNDC(drawxpos,drawypos-iLine++*yspace,sCollSysInfo.Data()); // "p-Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV"
			if (ptrange) l.DrawLatexNDC(drawxpos,drawypos-iLine++*yspace,ptrange);
			if (trigger) l.DrawLatexNDC(drawxpos,drawypos-iLine++*yspace,trigger); // "PHOS trigger", "min. bias trigger"
			if (bdrawdatasetinfo) {
				l.DrawLatexNDC(drawxpos,drawypos-iLine++*yspace,"Dataset:");
				l.DrawLatexNDC(drawxpos,drawypos-iLine++*yspace,Form("%s",dataset)); // "data, lhc13bc", "MC, lhc13b2_efix (DPMJET)"
			}
//			l.DrawLatexNDC(drawxpos,drawypos-iLine++*yspace,"ALICE Work in Progress");

		}


		void drawgenwindowMCP (const Char_t* rap, Float_t newxpos = 0., Float_t newypos = 0.) {

			l.SetTextFont(textfont);
			l.SetTextSize(textsize);

			Float_t drawxpos = xpos;
			Float_t drawypos = ypos;

			if (newxpos) drawxpos = newxpos;
			if (newypos) drawypos = newypos;

			l.DrawLatexNDC(drawxpos,drawypos-6*yspace,Form("generated %s's:",sAnalyzedParticle.Data()));
			if (strncmp(rap, "inf", 3)) {
				l.DrawLatexNDC(drawxpos,drawypos-7*yspace,"|#it{y}| < #infty, 0 < #it{#varphi} < 2#pi");
			}
			else if (strncmp(rap, "PHOS", 4)) {
				l.DrawLatexNDC(drawxpos,drawypos-7*yspace,Form("%s #rightarrow #gamma#gamma, both #gamma's on PHOS",sAnalyzedParticle.Data()));
			}
			else if (strncmp(rap, "AddedOnPHOS", 11)) {
				l.DrawLatexNDC(drawxpos,drawypos-7*yspace,Form("%s on PHOS",sAnalyzedParticle.Data()));
			}
			else {
				l.DrawLatexNDC(drawxpos,drawypos-7*yspace,Form("|#it{y}| < %s, 0 < #it{#varphi} < 2#pi",rap));
			}

		}


		void drawlegend (TObjArray* oa, Float_t newxpos = 0., Float_t newypos = 0., const Char_t* legopt = "ple", Bool_t bSysUnc = kFALSE) {

			Float_t drawlegx = legx;
			Float_t drawlegy = legy;

			if (newxpos) drawlegx = newxpos;
			if (newypos) drawlegy = newypos;

			TLegend* leg = new TLegend(drawlegx,drawlegy,drawlegx+0.2,drawlegy+ oa->GetEntries() * yspace);

			leg->SetBorderSize(0);
			leg->SetFillColor(0);

			leg->SetTextFont(textfont);
			leg->SetTextSize(textsize);

			if (sLegendText.IsNull()) {
				printf(" ### No text for the legend object given, please provide one! ### \n");
				return;
			}

			TObjArray* oLegendText = sLegendText.Tokenize(";");

			for (Int_t iEntry = 0; iEntry < oa->GetEntries(); iEntry++) {
				TObjString* osLegendText = (TObjString*) oLegendText->At(iEntry);
				if (strncmp(osLegendText->GetString().Data(), "", 1) || osLegendText->GetString() == 0x0) {
					printf(" ### No text for this legend object given, please provide one! ### ");
					continue;
				}
				if (bSysUnc) {
					if (iEntry < (oa->GetEntries())-1) leg->AddEntry(oa->At(iEntry),osLegendText->GetString().Data(),legopt);
					else leg->AddEntry(oa->At(iEntry),osLegendText->GetString().Data(),"l"); // when plotting systematic uncertainties last entry is RMS/quadratic sum
				}
				else leg->AddEntry(oa->At(iEntry),osLegendText->GetString().Data(),legopt);
			}

			leg->Draw("same");

		}


		void drawratioline (Double_t xmin = 0., Double_t xmax = 30., Double_t y = 1.) {

			TLine *line = new TLine(xmin,y,xmax,y);
			line->SetLineStyle(2);
			line->SetLineColor(kBlack);
			line->SetLineWidth(linewidth);

			line->Draw("same");

		}


		void drawtext (const Char_t* text, Float_t newxpos, Float_t newypos) {

			l.SetTextFont(textfont);
			l.SetTextSize(textsize);

			l.DrawLatexNDC(newxpos,newypos,text);

		}


		void SetTextfont (Int_t newtextfont) {
			textfont = newtextfont;
		}


		void SetTextsize (Int_t newtextsize) {
			textsize = newtextsize;
		}


		void SetMarkerstyle (Int_t newmarkerstyle) {
			markerstyle = newmarkerstyle;
		}


		void SetMarkersize (Float_t newmarkersize) {
			markersize = newmarkersize;
		}


		void SetLinewidth (Float_t newlinewidth) {
			linewidth = newlinewidth;
		}


		void SetLinestyle (Float_t newlinestyle) {
			linestyle = newlinestyle;
		}


		void SetXpos (Float_t newxpos) {
			xpos = newxpos;
		}


		void SetYpos (Float_t newypos) {
			ypos = newypos;
		}


		void SetYspace (Float_t newyspace) {
			yspace = newyspace;
		}


		void SetLegX (Float_t newlegx) {
			legx = newlegx;
		}


		void SetLegY (Float_t newlegy) {
			legy = newlegy;
		}


		void SetXTitleOffset (Float_t newxtitleoffset) {
			xtitleoffset = newxtitleoffset;
		}


		void SetYTitleOffset (Float_t newytitleoffset) {
			ytitleoffset = newytitleoffset;
		}


		void Setdrawalicelable (Bool_t newbdrawalicelable) {
			bdrawalicelable = newbdrawalicelable;
		}


		void Setdrawdatasetinfo (Bool_t newbdrawdatasetinfo) {
			bdrawdatasetinfo = newbdrawdatasetinfo;
		}


		void Setdrawrxinfo (Bool_t newbdrawrxinfo) {
			bdrawrxinfo = newbdrawrxinfo;
		}


		void SetAnalyzedParticle(TString newAnalyzedParticle) {
			sAnalyzedParticle = newAnalyzedParticle;
		}


		void SetCollSysInfoText (TString newsCollSysInfo) {
			sCollSysInfo = newsCollSysInfo;
		}


		void SetLegendText(TString sLeg) {
			sLegendText = sLeg;
		}


		TString GetAnalyzedParticle() {
			return sAnalyzedParticle;
		}


	private:

		TLatex l;

		Int_t textfont, textsize;
		Int_t markerstyle;
		Float_t markersize;
		Float_t linewidth, linestyle;
		Float_t xpos, ypos, yspace; // position of TLatex
		Float_t legx, legy; // position of TLegend

		Float_t xtitleoffset, ytitleoffset; // title offset of histogram axis

		Bool_t bdrawalicelable, bdrawdatasetinfo, bdrawrxinfo;

		TString sAnalyzedParticle, sCollSysInfo, sLegendText;


};


myStyle::myStyle () :
	textfont(43),
	textsize(30),
	markerstyle(20),
	markersize(2.0),
	linewidth(2.0),
	linestyle(1),
	xpos(0.65),
	ypos(0.9),
	yspace(0.045),
	legx(0.35),
	legy(0.75),
	xtitleoffset(1.1),
	ytitleoffset(1.2),
	bdrawalicelable(kFALSE),
	bdrawdatasetinfo(kTRUE),
	bdrawrxinfo(kTRUE),
	sAnalyzedParticle("#eta"),
	sCollSysInfo("p-Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV"),
	sLegendText("")
	{
		std::cout << "Loading my style...\n";
	}


myStyle::~myStyle ()
	{
		std::cout << "Style is gone...\n";
	}

#endif
