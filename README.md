# Lightstrip Audio Visualization
Couple programs utilizing MSGEQ7 IC with FastLED to produce stunning audio-visual effects.

You can find the circuit diagaram here: https://os.mbed.com/media/uploads/chrisisthefish/equalizerschematic.png
Modify pin outs to suit your needs and adjust noisethreshold to what you see fit.

From EEWeb:
" The way this works is that we feed an audio signal into the MSGEQ7’s AUDIO_IN input via a 22-KΩ resistor and a 0.1-μF ceramic decoupling capacitor (we’ll talk about potential sources of the audio input in my next column on this topic). The purpose of the decoupling capacitor is to remove any DC bias on the audio signal (we’ll talk about this in my next column on this topic also).

The MSGEQ7 constantly analyzes the incoming audio signal and splits it into seven different frequency bands centered on 63 Hz, 160 Hz, 400 Hz, 1,000 Hz, 2,500 Hz, 6,250 Hz, and 16,000 Hz. When we apply a positive-going pulse to the MSGEQ’s RESET input, it latches the current frequency band values. Next, we apply a series of seven negative-going pulses to the MSGEQ’s STROBE input to read out the values associated with each of the seven frequency bands.

In the case of a 5-V system, as illustrated above (the MSGEQ7 also works with 3.3-V systems), the frequency values are presented as analog voltages between 0 V and 5 V. We access these values using one of the Arduino’s analog inputs (A0 in the diagram above), and the analogRead() function converts them into corresponding integer values between 0 and 1023. "


I recommend using the basic program to work out flaws in your circuit using LEDs hooked up to Arduino's PWM outputs before migrating to the lightstrip.
