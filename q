[1mdiff --git a/bin/dtwmatch b/bin/dtwmatch[m
[1mindex 2cc25ea..2ce1637 100755[m
Binary files a/bin/dtwmatch and b/bin/dtwmatch differ
[1mdiff --git a/bin/genspect b/bin/genspect[m
[1mindex bca161b..ccbc481 100755[m
Binary files a/bin/genspect and b/bin/genspect differ
[1mdiff --git a/data/plot_spect.py b/data/plot_spect.py[m
[1mindex e691d93..7694801 100644[m
[1m--- a/data/plot_spect.py[m
[1m+++ b/data/plot_spect.py[m
[36m@@ -19,7 +19,7 @@[m [mbeg_idx = -1[m
 if sys.argv[1] == "sp":[m
     beg_idx = 0[m
 elif sys.argv[1] == "ce":[m
[31m-    beg_idx = 1[m
[32m+[m[32m    beg_idx = 2[m
 [m
 if beg_idx == -1:[m
     sys.exit();[m
[36m@@ -59,6 +59,5 @@[m [mplt.title(sys.argv[2]);[m
 plt.imshow(X=rot_spect, cmap='hot', interpolation='nearest')[m
 name,suffix = sys.argv[2].split(".")[m
 plt.show()[m
[31m-#plt.imsave(fname=name+'.png', arr=rot_spect, cmap='hot', format='png')[m
 [m
 fd.close()[m
[1mdiff --git a/inc/cepstratrans.h b/inc/cepstratrans.h[m
[1mindex 5fc057b..9287b64 100644[m
[1m--- a/inc/cepstratrans.h[m
[1m+++ b/inc/cepstratrans.h[m
[36m@@ -42,8 +42,8 @@[m [mnamespace dsp[m
 	  for(ce_idx = 0; ce_idx < cepstra.width(); ++ce_idx)[m
 	    {[m
 	      ce_val = 0;[m
[31m-	      phase = ce_idx * 2;[m
[31m-	      delta_phase = ce_idx * 4;[m
[32m+[m	[32m      phase = ce_idx;[m
[32m+[m	[32m      delta_phase = ce_idx * 2;[m
 [m
 	      //Traverse elements of spectrogram[m
 	      for(sp_idx = 0; sp_idx < _N; ++sp_idx, phase += delta_phase)[m
