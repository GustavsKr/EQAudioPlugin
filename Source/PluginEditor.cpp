#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p)
{
    // Helper lambda to setup knobs quickly
    auto setupSlider = [this](juce::Slider& s, juce::String paramID, bool isDb) {
        s.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        if (isDb) {
            s.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
            s.setTextValueSuffix(" dB");
        }
        else {
            s.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        }
        addAndMakeVisible(s);
        attachments.push_back(std::make_unique<Attachment>(processorRef.apvts, paramID, s));
        };

    // Initialize all
    setupSlider(inputSlider, "INPUT", true);
    setupSlider(gateSlider, "GATE", true);
    setupSlider(outputSlider, "OUTPUT", true);

    setupSlider(gainSlider, "GAIN", false);
    setupSlider(bassSlider, "BASS", false);
    setupSlider(midSlider, "MIDDLE", false);
    setupSlider(trebleSlider, "TREBLE", false);
    setupSlider(presenceSlider, "PRESENCE", false);
    setupSlider(levelSlider, "LEVEL", false);

    setSize(700, 450);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics& g)
{
    // 1. Background - A dark "Tolex" style or charcoal grey
    g.fillAll(juce::Colour(30, 30, 30));

    // 2. Decorative Panels (Optional but looks cool)
    auto topArea = getLocalBounds().removeFromTop(getHeight() * 0.25f);
    g.setColour(juce::Colours::black.withAlpha(0.3f));
    g.fillRect(topArea); // Darker strip for the utility knobs

    // 3. Set Font and Color for Labels
    g.setColour(juce::Colours::whitesmoke);
    g.setFont(14.0f);

    // Helper function to draw text centered above a slider
    auto drawLabel = [&g](juce::Slider& slider, juce::String text)
        {
            // Place text 20 pixels above the slider bounds
            auto labelArea = slider.getBounds().withY(slider.getY() - 18).withHeight(20);
            g.drawText(text, labelArea, juce::Justification::centred);
        };

    // --- Draw Labels for Top Row ---
    drawLabel(inputSlider, "INPUT");
    drawLabel(gateSlider, "GATE");
    drawLabel(outputSlider, "OUTPUT");

    // --- Draw Labels for Main Amp Row ---
    g.setFont(16.0f); // Make main knobs slightly larger text
    drawLabel(gainSlider, "GAIN");
    drawLabel(bassSlider, "BASS");
    drawLabel(midSlider, "MIDDLE");
    drawLabel(trebleSlider, "TREBLE");
    drawLabel(presenceSlider, "PRESENCE");
    drawLabel(levelSlider, "LEVEL");

    // 4. Branding / Versioning
    g.setColour(juce::Colours::orange);
    g.setFont(juce::Font("Impact", 20.0f, juce::Font::plain));
    g.drawText("AMP SIM", getLocalBounds().reduced(20), juce::Justification::bottomLeft);
}

void AudioPluginAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(10);

    // 1. Top Row (Utility Bar) - Roughly 25% of height
    auto topRow = area.removeFromTop(area.getHeight() * 0.30f);

    // Input and Gate on the left
    auto topLeft = topRow.removeFromLeft(topRow.getWidth() * 0.4f);
    inputSlider.setBounds(topLeft.removeFromLeft(topLeft.getWidth() * 0.5f));
    gateSlider.setBounds(topLeft);

    // Output on the right
    outputSlider.setBounds(topRow.removeFromRight(topRow.getWidth() * 0.25f));

    // 2. Main Row (Amp Knobs) - The rest of the space
    area.removeFromTop(20); // padding
    auto knobWidth = area.getWidth() / 6;
    gainSlider.setBounds(area.removeFromLeft(knobWidth));
    bassSlider.setBounds(area.removeFromLeft(knobWidth));
    midSlider.setBounds(area.removeFromLeft(knobWidth));
    trebleSlider.setBounds(area.removeFromLeft(knobWidth));
    presenceSlider.setBounds(area.removeFromLeft(knobWidth));
    levelSlider.setBounds(area.removeFromLeft(knobWidth));
}