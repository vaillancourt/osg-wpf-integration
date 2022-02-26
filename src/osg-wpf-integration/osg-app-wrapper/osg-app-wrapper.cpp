#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include <utility>
#include <limits.h>
#include "osg-app-wrapper.h"

#include <osgViewer/Viewer>
#include <osg/GraphicsContext>
#include <osgViewer/api/Win32/GraphicsWindowWin32>
#include <osgDB/ReaderWriter>
#include <osgDB/ReadFile>
#include <thread>
#include <atomic>

#include <cassert>


struct InstanceData;
void osgWpf_FrameImpl(InstanceData* aInstanceData);


struct InstanceData
{
    osg::ref_ptr<osgViewer::Viewer> _osgViewer;
    int32_t _frameCount{};
    std::thread _thread;

};

static InstanceData* _instanceData{};
static std::atomic<bool> _run{ true };

class Test final
{
public:

    void operator()()
    {
        while (_run)
        {
            osgWpf_FrameImpl(_instanceData);
        }
    }
    //InstanceData* _instanceData{};
};

void osgWpf_Init(HWND aHandle)
{
    assert(not _instanceData);

    _instanceData = new InstanceData();

    _instanceData->_osgViewer = new osgViewer::Viewer();
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits();
    traits->inheritedWindowData = new osgViewer::GraphicsWindowWin32::WindowData(aHandle, true);

    traits->x = 0;
    traits->y = 0;

    {
        ::RECT rect;

        ::GetWindowRect(aHandle, &rect);

        traits->width = rect.right - rect.left;
        traits->height = rect.bottom - rect.top;
    }
    traits->windowDecoration = false;
    traits->doubleBuffer = true;
    traits->pbuffer = false;
    traits->setInheritedWindowPixelFormat = true;

    osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
    gc->setClearColor(osg::Vec4(1, 0, 1, 1));

    _instanceData->_osgViewer->getCamera()->setGraphicsContext(gc);

    _instanceData->_osgViewer->getCamera()->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
    _instanceData->_osgViewer->getCamera()->setDrawBuffer(GL_BACK);
    _instanceData->_osgViewer->getCamera()->setReadBuffer(GL_BACK);
    _instanceData->_osgViewer->getCamera()->setViewMatrixAsLookAt(osg::Vec3d(50, 0, 0), osg::Vec3d(), osg::Vec3d(0, 0, 1));
    _instanceData->_osgViewer->getCamera()->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    _instanceData->_osgViewer->getCamera()->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(traits->width) / static_cast<double>(traits->height), 1.0, 1000.0);

    _instanceData->_osgViewer->setSceneData(osgDB::readRefNodeFile("C:\\DevTools\\OpenSceneGraph-3.6.5\\OpenSceneGraph-Data\\cessna.osgt"));
    _instanceData->_osgViewer->realize();
    _instanceData->_osgViewer->frame();
    _instanceData->_thread = std::thread(Test());
}

void osgWpf_ShutDown()
{
    if (_instanceData->_thread.joinable())
    {
        _run = false;
        _instanceData->_thread.join();
    }

    if (_instanceData)
        delete _instanceData;
    _instanceData = nullptr;
}


void osgWpf_FrameImpl(InstanceData* aInstanceData)
{
    if (not aInstanceData)
        return;

    double angle = (aInstanceData->_frameCount % 360) / 360.0 * 2.0 * osg::PI;
    aInstanceData->_osgViewer->getCamera()->setViewMatrixAsLookAt(osg::Vec3d(
        50 * ::cos(angle), 50 * ::sin(angle), 0), osg::Vec3d(), osg::Vec3d(0, 0, 1));
    aInstanceData->_osgViewer->frame();
    aInstanceData->_frameCount++;
}


void osgWpf_Frame()
{
    if (not _instanceData)
        return;

    osgWpf_FrameImpl(_instanceData);
}


// DLL internal state variables:
static unsigned long long previous_;  // Previous value, if any
static unsigned long long current_;   // Current sequence value
static unsigned index_;               // Current seq. position


uint64_t fibonacci_return42()
{
    return 42;
}

// Initialize a Fibonacci relation sequence
// such that F(0) = a, F(1) = b.
// This function must be called before any other function.
void fibonacci_init(
    uint64_t a,
    uint64_t b)
{
    index_ = 0;
    current_ = a;
    previous_ = b; // see special case when initialized
}

// Produce the next value in the sequence.
// Returns true on success, false on overflow.
bool fibonacci_next()
{
    // check to see if we'd overflow result or position
    if ((ULLONG_MAX - previous_ < current_) ||
        (UINT_MAX == index_))
    {
        return false;
    }

    // Special case when index == 0, just return b value
    if (index_ > 0)
    {
        // otherwise, calculate next sequence value
        previous_ += current_;
    }
    std::swap(current_, previous_);
    ++index_;
    return true;
}

// Get the current value in the sequence.
unsigned long long fibonacci_current()
{
    return current_;
}

// Get the current index position in the sequence.
unsigned fibonacci_index()
{
    return index_;
}