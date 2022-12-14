#include <iostream>

#include "mprpcapplication.h"
#include "friends.pb.h"
#include "mprpcchannel.h"

int main(int argc, char *argv[])
{
    //整个程序启动以后，想使用mprpc框架来享受rpc服务调用，一定需要先调用框架的初始化函数（只初始化一次）
    MprpcApplication::Init(argc, argv);

    //演示调用远程发布的rpc方法Login
    friends::FriendServiceRpc_Stub stub(new MprpcChannel());

    // rpc方法的请求参数
    friends::GetFriendsListRequest request;
    request.set_userid(100); // 设置用户的id号

    // rpc方法的响应
    friends::GetFriendsListResponse response;
    // 发起rpc方法的调用 同步的rpc调用过程  MprpcChannel::callmethod
    MprpcController controller;
    stub.GetFriendsList(&controller, &request, &response, nullptr);
    // RpcChannel->RpcChannel::callMethod 集中来做所有rpc方法调用的参数序列化和网络发送

    // 一次rpc调用完成，读调用的结果
    if (0 == response.result().errcode()) // 响应成功
    {
        std::cout << "rpc GetFriendList response success!" << std::endl;
        int size = response.friends_size(); // 获取好友的数量
        for (int i = 0; i < size; ++i)
        {
            std::cout << "index: " << (i + 1) << " name: " << response.friends(i) << std::endl;
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "rpc GetFriendList response error : " << response.result().errmsg() << std::endl;
    }

    return 0;
}
