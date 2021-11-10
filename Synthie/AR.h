#pragma once
#include "AudioNode.h"
class CAR :
    public CAudioNode
{
public:

    //! Start audio generation
    virtual void Start();

    void SetSource(CAudioNode* node) { m_source = node; }

    virtual bool Generate() override;

    void SetDuration(double duration) { m_duration = duration; }

    void SetTime(double time) { m_time = time; }

private:
    double m_attack = 0.05;
    double m_release = 0.05;
    double m_duration;
    double m_time;

    CAudioNode* m_source;
};

