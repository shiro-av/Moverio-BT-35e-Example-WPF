   M S B A M L   `   `   `  ����U  QLiveCharts.Wpf, Version=0.9.7.0, Culture=neutral, PublicKeyToken=0bc1f845d1ebb8dfG4clr-namespace:LiveCharts.Wpf;assembly=LiveCharts.WpfLiveCharts.Wpf  5       SampleSensorDataChart8   2SampleSensorDataChart.Sensors.GravityVectorControl   5
      R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5      R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5      @d2http://schemas.microsoft.com/expression/blend/2008     5      Dlvc4clr-namespace:LiveCharts.Wpf;assembly=LiveCharts.Wpf     5      Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5        � 	Resources  5      #   LiveCharts.Wpf.CartesianChart �� 
TargetType �� Property �� Value��%�   '        '�� H     �� 5   
   "  6   .�5      ��  � ��$ 10q�6'   5      �� 5   
   " ��6   .�5      ��  � ��$ 20(�6)   �� 5       � ��$ 5,5,5,0q�6'   5      5      .��5      �  � RowDefinitions 5   
   �� 5      �� 5      $
��Auto �6   .+�5"   
     -   5          Name$ chart��5#      &    LiveCharts.Wpf.Charts.Base.Chart   DisableAnimations .    	Hoverable .     DataTooltip 5$      Z� 	   Series	 5(         LiveCharts.Wpf.LineSeries     LiveCharts.Wpf.Series
   Fill

 ����    Stroke
 � � �   PointGeometry 5*      Z�    Values 5,      �� *	ValuesX+  5-      

 ���� 
 ��  � 5/      Z�  51      �� *	ValuesY+  52      

 ���� 
 �  �� 54      Z�  56      �� *	ValuesZ+58      �� 5:   
   $��1��6   .+�5;      ��  �� Orientation$ 
Horizontal=�6   .+�5<      �� 
��� � �$
��X : ��6/   �� 5=      -   5         ��Name$ AxisX��5=      
��� � �6+   5>      �� 5?      $ 
Horizontal=�6   .+�5@      �� 
����  �$
��Y : ��6.   �� 5A      -   5        $ AxisY��5A      
����  �6+   5B      �� 5C      $ 
Horizontal=�6   .+�5D      �� 
���  ��$
��Z : ��6-   �� 5E      -   5        $ AxisZ��5E      
���  ��6+   5F      5G      5H      5I      