   M S B A M L   `   `   `  ����H  DMahApps.Metro, Version=1.6.5.1, Culture=neutral, PublicKeyToken=nullV;clr-namespace:MahApps.Metro.Controls;assembly=MahApps.MetroMahApps.Metro.Controls  5       Sample2D3DControl"   Sample2D3DControl.MainWindow   5
      R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5      R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5      PControls;clr-namespace:MahApps.Metro.Controls;assembly=MahApps.Metro     5      @d2http://schemas.microsoft.com/expression/blend/2008     5      Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5      -   5          � Title$  Sample2D3DControl��5      $	��310��5      $	��190��5       � 
ResizeMode$ NoResize=�5      .��5      �  � 	Resources 5   
      	TextStyle �� 
TargetType �� Property �� Value  2D3DTextStyle �� BasedOn  	GetButton  MetroButton  	SetButton��%�  &	        &	 �     7   &	 D    7  &	 �    7  �� 5      " ��6&   .�5      ��  � ��$ Center=�66   �� 5       � ��$ 2q�6+   �� 5       � ��$ 20(�6-   5      �� 5      8   " ��5!      .�5"      ��  � ��$ 2,2,20,2q�6+   �� 5#       � ��$ 60��6*   �� 5$       �@��TextAlignment$ Center=�62   5%      �� 5&      8   " ��5)      .�5*      ��  � ��$ 60��6*   �� 5+       � ��$ 2q�6+   �� 5,       � ��$ 20(�6-   �� 5-       � {� .  6.   5.      �� 5/      8   " ��52      .�53      ��  � ��$ 50��6*   �� 54       � ��$ 10q�6+   �� 55       � ��$ 20(�6-   �� 56       � {� .  6.   57      58       � RowDefinitions 59   
   �� 5:      $
��Auto �6   �� 5;      $
��Auto �6   .+�5>   
   �� $��10q�6    �� Orientation$ 
Horizontal=�6!   .+�5?      �� #��[  6   $��Current 2D/3D:��6;   �� 5@      -   5        	 ��Name$	 Current2D3D��5A      #��[ 5B      $��-��5C      �� 5D      -   5        
 ��Name$
 	ButtonGet��5E      $	��Get��5G      #��[ 5H      5I      �� 5J   
   $��1��6   $��
10,0,10,10q�6"   .+�5K      �� #��[  6   $��
Set 2D/3D:��6;   �� 5L      $ 
Horizontal=�6   .+�5M      �� -   5        $
 Button2D��5N      $��2D��5P      #��[ 5Q      �� 5R      -   5        $
 Button3D��5S      $��3D��5U      #��[ 5V      5W      5X      5Y      5Z      