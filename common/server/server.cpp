#include <iostream>

#include "server.h"

using namespace tetris;

TetrisServer::TetrisServer(asio::io_service& io_context, tcp::endpoint& endpoint):
    acceptor(io_context, endpoint) {
    
}

void TetrisServer::Accept() {
    acceptor.async_accept(
        [this](std::error_code ec, tcp::socket socket)
        {
          if (!ec)
          {
            std::make_shared<TetrisPlayer>(std::move(socket));
          }

          Accept();
        });
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "syntax: " << argv[0] << " port" << std::endl;
        return 1;
    }

    asio::io_context io_context;
    tcp::endpoint endpoint(tcp::v4(), atoi(argv[1]));

    TetrisServer server(io_context, endpoint);
    server.Accept();

    io_context.run();

    return 0;
}
