import numpy as np
import ROOT

'''
Loading the Data from file
'''
data_650_1 = np.loadtxt('/home/apmnair18/Github/Calculation_of_muon_life_in_Geant4/Data_and_Plots/Real_Data/650_196.5.data')
data_650_2 = np.loadtxt('/home/apmnair18/Github/Calculation_of_muon_life_in_Geant4/Data_and_Plots/Real_Data/650_216.7.data')
data_700_1 = np.loadtxt('/home/apmnair18/Github/Calculation_of_muon_life_in_Geant4/Data_and_Plots/Real_Data/700_198.4.data')
data_700_2 = np.loadtxt('/home/apmnair18/Github/Calculation_of_muon_life_in_Geant4/Data_and_Plots/Real_Data/700_216.7.data')
data_750_1 = np.loadtxt('/home/apmnair18/Github/Calculation_of_muon_life_in_Geant4/Data_and_Plots/Real_Data/750_196.5.data')
data_750_2 = np.loadtxt('/home/apmnair18/Github/Calculation_of_muon_life_in_Geant4/Data_and_Plots/Real_Data/750_216.7.data')


data_650_1 = [data_650_1[:,0][i] for i in range(len(data_650_1[:,0])) if data_650_1[:,0][i] < 40000]
data_650_2 = [data_650_2[:,0][i] for i in range(len(data_650_2[:,0])) if data_650_2[:,0][i] < 40000]
data_700_1 = [data_700_1[:,0][i] for i in range(len(data_700_1[:,0])) if data_700_1[:,0][i] < 40000]
data_700_2 = [data_700_2[:,0][i] for i in range(len(data_700_2[:,0])) if data_700_2[:,0][i] < 40000]
data_750_1 = [data_750_1[:,0][i] for i in range(len(data_750_1[:,0])) if data_750_1[:,0][i] < 40000]
data_750_2 = [data_750_2[:,0][i] for i in range(len(data_750_2[:,0])) if data_750_2[:,0][i] < 40000]



hist,canvas = None,None
hist = ROOT.TH1F("hist", "V_th = 196.5mV V_op = 650V", 60, min(data_650_1), max(data_650_1))
for value in data_650_1:
    hist.Fill(value)



canvas = ROOT.TCanvas("canvas", "V_th = 196.5mV V_op = 650V", 1000, 600)
hist.Draw()

canvas.Draw()

ROOT.gApplication.Run()

ROOT.gApplication.close()