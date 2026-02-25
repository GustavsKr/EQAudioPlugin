#pragma once

#include "PluginProcessor.h"

//==============================================================================
class AudioPluginAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // Utility Knobs (Top)
    juce::Slider inputSlider, gateSlider, outputSlider;
    // Main Knobs (Bottom)
    juce::Slider gainSlider, bassSlider, midSlider, trebleSlider, presenceSlider, levelSlider;

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::vector<std::unique_ptr<Attachment>> attachments;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
