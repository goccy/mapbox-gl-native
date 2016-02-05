//
//  MapView.hpp
//  Pods
//
//  Created by masaaki.goshima on 2016/02/05.
//
//

#ifndef MapView_hpp
#define MapView_hpp

#include <stdio.h>

class MapView {
public:
    MapView(void);
    virtual ~MapView(void);
    bool init(void);
    static MapView *create(void);
};

#endif /* MapView_hpp */
