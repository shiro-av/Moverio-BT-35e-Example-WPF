   M S B A M L   `   `   `  ����U  QLiveCharts.Wpf, Version=0.9.7.0, Culture=neutral, PublicKeyToken=0bc1f845d1ebb8dfG4clr-namespace:LiveCharts.Wpf;assembly=LiveCharts.WpfLiveCharts.Wpf  5       SampleSensorDataChart7   1SampleSensorDataChart.Sensors.AmbientLightControl   5
      R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5      R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5      @d2http://schemas.microsoft.com/expression/blend/2008     5      Dlvc4clr-namespace:LiveCharts.Wpf;assembly=LiveCharts.Wpf     5      Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5        � 	Resources  5      #   LiveCharts.Wpf.CartesianChart �� 
TargetType �� Property �� Value��%�   '        '�� H     �� 5   
   "  6   .�5      ��  � ��$ 10q�6'   5      �� 5   
   " ��6   .�5      ��  � ��$ 20(�6)   �� 5       � ��$ 5,5,5,0q�6'   5      5      .��5      �  � RowDefinitions 5   
   �� 5      �� 5      $
��Auto �6   .+�5"   
     -   5          Name$ chart��5#      &    LiveCharts.Wpf.Charts.Base.Chart   DisableAnimations .    	Hoverable .     DataTooltip 5$      Z� 	   Series	 5(         LiveCharts.Wpf.LineSeries     LiveCharts.Wpf.Series
   Fill

 ����    Stroke
 � ���   PointGeometry 5*      Z�    Values 5,      �� *ValuesBrightness+5.      �� 50   
   $��1��6   .+�51      ��  �� Orientation$ 
Horizontal=�6   .+�52      �� 
��� ���$��Brightness : ��60   �� 53      -   5         ��Name$ 
Brightness��53      
��� ���60   54      55      56      57      