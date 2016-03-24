////
////  ShowPolygonLayer.hpp
////  kancolle_beta
////
////  Created by 岩林张 on 3/8/16.
////
////
//
//#ifndef ShowPolygonLayer_hpp
//#define ShowPolygonLayer_hpp
//
//#include "cocos2d.h"
//
//USING_NS_CC;
//
//
//class TriangleCommand:public CustomCommand
//{
//public:
//    TriangleCommand();
//    
//    void init(int globalOrder,GLProgram* shader,Vec3* vertices,Color4F* colors,GLuint* indices,int indexCount,const Mat4& mv);
//    
//private:
//    void useMaterial();
//    void onDraw();
//    
//    Color4F* _squareColors;
//    Vec3* _noMVPVertices;
//    GLuint* _indices;
//    int _vertexCount;
//    Mat4 _mv;
//    GLProgram* _shader;
//};
//
//
//
//class ShowPolygonLayer:public Node
//{
//public:
//    static ShowPolygonLayer* create(const Color4B& color,Rect& rect);
//    
//    bool init(const Color4B& color,Rect& rect);
//    
//    void setRectangle(Rect& rect);
//    
//    void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
//private:
//    TriangleCommand customCommand;
//    Vec2* _squareVertices;
//    Vec3* _noMVPVertices;
//    GLuint* indices;
//    Color4F* colors;
//    
//    
//    Color4B color;
//    Rect rect;
//    
//    
//};
//
//
//
//#endif /* ShowPolygonLayer_hpp */
