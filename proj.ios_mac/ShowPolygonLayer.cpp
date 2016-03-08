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
//void ShowPolygonLayer::setRectangle(cocos2d::Rect &rect)
//{
//    Size size=Director::getInstance()->getVisibleSize();
//    
//}