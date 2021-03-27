
#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#ifdef BAZEL_BUILD
#include "examples/protos/distribution.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
// using helloworld::HelloRequest;
// using helloworld::HelloReply;
// using helloworld::Greeter;

using distribution::DistributionRequest;
using distribution::DistributionReply;
using distribution::Mechanism;

// class GreeterClient {
//  public:
//   GreeterClient(std::shared_ptr<Channel> channel)
//       : stub_(Greeter::NewStub(channel)) {}

//   // Assembles the client's payload, sends it and presents the response back
//   // from the server.
//   std::string SayHello(const std::string& user) {
//     // Data we are sending to the server.
//     HelloRequest request;
//     request.set_name(user);

//     // Container for the data we expect from the server.
//     HelloReply reply;

//     // Context for the client. It could be used to convey extra information to
//     // the server and/or tweak certain RPC behaviors.
//     ClientContext context;

//     // The actual RPC.
//     Status status = stub_->SayHello(&context, request, &reply);

//     // Act upon its status.
//     if (status.ok()) {
//       return reply.message();
//     } else {
//       std::cout << status.error_code() << ": " << status.error_message()
//                 << std::endl;
//       return "RPC failed";
//     }
//   }

//  private:
//   std::unique_ptr<Greeter::Stub> stub_;
// };


class DistributionClient {
    public:
DistributionClient(std::shared_ptr<Channel> channel) : stub_(Mechanism::NewStub(channel)) {}


std::string contactServer(const std::string& messageToSend){

    DistributionRequest request;
    request.set_message(messageToSend);
    DistributionReply reply;

    ClientContext context;

    Status status = stub_->contactServer(&context, request, &reply);

    if(status.ok()){
        return reply.message();
    } else {
        return "Error";
    }

}



 private:
  std::unique_ptr<Mechanism::Stub> stub_;
};

int main(int argc, char** argv) {

  std::string target_str = "localhost:50051";

  DistributionClient dc(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
  std::string msgToSend("Sent this message");
  std::string msgToSend2("Adam");
  std::string msgToSend3("Dave");
  std::string msgToSend4("Ciara");
  std::string reply2 = dc.contactServer(msgToSend);
  std::string reply3 = dc.contactServer(msgToSend2);
  std::string reply4 = dc.contactServer(msgToSend3);
  std::string reply5 = dc.contactServer(msgToSend4);
  std::cout << "Reply: " << reply2 << std::endl;
  std::cout << "Reply: " << reply3 << std::endl;
  std::cout << "Reply: " << reply4 << std::endl;
  std::cout << "Reply: " << reply5 << std::endl;

  return 0;
}
