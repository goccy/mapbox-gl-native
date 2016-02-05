//
//  MapView.cpp
//  Pods
//
//  Created by masaaki.goshima on 2016/02/05.
//
//

#include "MapView.hpp"

#import <mbgl/platform/log.hpp>
#import <mbgl/platform/gl.hpp>

MapView::MapView(void)
{
    
}

MapView::~MapView(void)
{
    
}

bool MapView::init(void)
{
    return true;
}

MapView *MapView::create(void)
{
    MapView *ret = new MapView();
    if (ret && ret->init()) {
        return ret;
    }
    if (ret) {
        delete ret;
    }
    return NULL;
}