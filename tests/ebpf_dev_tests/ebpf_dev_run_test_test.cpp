#include <gtest/gtest.h>

extern "C" {
#include <stdint.h>
#include <errno.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/ebpf.h>
#include <sys/ebpf_dev.h>
}

namespace {
class EbpfDevRunTestTest : public ::testing::Test {
  protected:
    int ebpf_fd;

    virtual void
    SetUp()
    {
        int error;

        ebpf_fd = open("/dev/ebpf", O_RDWR);
        assert(ebpf_fd > 0);
    }

    virtual void
    TearDown()
    {
        close(ebpf_fd);
    }
};

TEST_F(EbpfDevRunTestTest, LoadCtxToR0AndReturn)
{
    int error, prog_fd;

    struct ebpf_inst insts[] = {
        {EBPF_OP_LDXDW, 0, 1, 0, 0},
        {EBPF_OP_EXIT, 0, 0, 0, 0}
    };

    union ebpf_req req;
    req.prog_fdp = &prog_fd;
    req.prog_type = EBPF_PROG_TYPE_TEST;
    req.prog = insts;
    req.prog_len = 2;
    req.map_flags = 0;

    error = ioctl(ebpf_fd, EBPFIOC_LOAD_PROG, &req);
    assert(!error);

    uint64_t ctx = 100, result;

    union ebpf_req test_req;
    test_req.prog_fd = prog_fd;
    test_req.ctx = &ctx;
    test_req.ctx_len = sizeof(uint64_t);
    test_req.jit = 0;
    test_req.test_result = &result;

    error = ioctl(ebpf_fd, EBPFIOC_RUN_TEST, &test_req);
    EXPECT_EQ(0, error);
    EXPECT_EQ(100, result);
}
}