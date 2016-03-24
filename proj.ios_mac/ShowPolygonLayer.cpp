////
////  ShowPolygonLayer.cpp
////  kancolle_beta
////
////  Created by 岩林张 on 3/8/16.
////
////
//
//#include "ShowPolygonLayer.hpp"
//
//
//void TriangleCommand::onDraw()
//{
//    useMaterial();
//    
//    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION|GL::VERTEX_ATTRIB_FLAG_COLOR);
//    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, _noMVPVertices);
//    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, _squareColors);
//    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, _indices);
//}
//
//ShowPolygonLayer* ShowPolygonLayer::create(const cocos2d::Color4B &color, cocos2d::Rect &rect)
//{
//    ShowPolygonLayer* bRet=new ShowPolygonLayer;
//    if (bRet&&bRet->init(color, rect))
//    {
//        bRet->autorelease();
//        return bRet;
//    }
//    delete bRet;
//    bRet=NULL;
//    return NULL;
//    
//}
//
//bool ShowPolygonLayer::init(const cocos2d::Color4B &color, cocos2d::Rect &rect)
//{
//    this->color=color;
//    this->rect=rect;
//    
//    bool bRet=false;
//    do
//    {
//        if (!Node::init())
//        {
//            break;
//        }
//        
//        _squareVertices=new Vec2[8];
//        _noMVPVertices=new Vec3[8];
//        colors=new Color4F[8];
//        indices=new GLuint[8];
//        
//        bRet=true;
//    }while(0);
//    return bRet;
//}
//
//
//
//void ShowPolygonLayer::setRectangle(cocos2d::Rect &rect)
//{
//    Size size=Director::getInstance()->getVisibleSize();
//    
//    _squareVertices[0]=Vec2(0.0, 0.0);
//    _squareVertices[1]=Vec2(size.width, 0.0);
//    _squareVertices[2]=Vec2(rect.origin.x, rect.origin.y);
//    _squareVertices[3]=Vec2(rect.origin.x+rect.size.width, rect.origin.y);
//    _squareVertices[4]=Vec2(size.width, size.height);
//    _squareVertices[5]=Vec2(rect.origin.x+rect.size.width, rect.origin.y+rect.size.height);
//    _squareVertices[6]=Vec2(rect.origin.x, rect.origin.y+rect.size.height);
//    _squareVertices[7]=Vec2(0.0, size.height);
//}
//
//void ShowPolygonLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
//{
//    for (int i=0; i<8; ++i)
//    {
//        Vec4 pos;
//        pos.x=_squareVertices[i].x;
//        pos.y=_squareVertices[i].y;
//        pos.z=getPositionZ();
//        pos.w=1;
//        
//        _modelViewTransform.transformVector(&pos);
//        _noMVPVertices[i]=Vec3(pos.x, pos.y, pos.z)/pos.w;
//    }
//    
//    customCommand.init(_globalZOrder, getGLProgram(), _noMVPVertices, colors, indices, 24, _modelViewTransform);
//    Director::getInstance()->getRenderer()->addCommand(&customCommand);
//}
//
//
