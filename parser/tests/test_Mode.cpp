#include "parserTester.hpp"

static void testOnlyCmd()
{
    std::vector<std::string> in = split("MODE");
    try
    {
        Mode cmd(in);
        assert(false);
    }
    catch (std::exception &e) {}
}

static void testCmdAndTargetAndMode()
{
    // Test setting and removing invite-only mode
    std::vector<std::string> in1 = split("MODE #channel +i");
    try
    {
        Mode cmd1(in1);
        assert(cmd1.getTarget() == "channel");
        assert(cmd1.getMode() == "+i");
        assert(cmd1.getOptional().empty());
    }
    catch (std::exception &e)
    {
        assert(false);
    }

    std::vector<std::string> in2 = split("MODE #channel -i");
    try
    {
        Mode cmd2(in2);
        assert(cmd2.getTarget() == "channel");
        assert(cmd2.getMode() == "-i");
        assert(cmd2.getOptional().empty());
    }
    catch (std::exception &e)
    {
        assert(false);
    }

    // Test setting and removing topic restrictions for channel operators
    std::vector<std::string> in3 = split("MODE #channel +t");
    try
    {
        Mode cmd3(in3);
        assert(cmd3.getTarget() == "channel");
        assert(cmd3.getMode() == "+t");
        assert(cmd3.getOptional().empty());
    }
    catch (std::exception &e)
    {
        assert(false);
    }

    std::vector<std::string> in4 = split("MODE #channel -t");
    try
    {
        Mode cmd4(in4);
        assert(cmd4.getTarget() == "channel");
        assert(cmd4.getMode() == "-t");
        assert(cmd4.getOptional().empty());
    }
    catch (std::exception &e)
    {
        assert(false);
    }

    // Test setting and removing channel key (password)
    std::vector<std::string> in5 = split("MODE #channel +k password123");
    try
    {
        Mode cmd5(in5);
        assert(cmd5.getTarget() == "channel");
        assert(cmd5.getMode() == "+k");
        assert(cmd5.getOptional() == "password123");
    }
    catch (std::exception &e)
    {
        assert(false);
    }

    std::vector<std::string> in6 = split("MODE #channel -k");
    try
    {
        Mode cmd6(in6);
        assert(cmd6.getTarget() == "channel");
        assert(cmd6.getMode() == "-k");
        assert(cmd6.getOptional().empty());
    }
    catch (std::exception &e)
    {
        assert(false);
    }

    // Test giving and taking channel operator privilege
    std::vector<std::string> in7 = split("MODE #channel +o user123");
    try
    {
        Mode cmd7(in7);
        assert(cmd7.getTarget() == "channel");
        assert(cmd7.getMode() == "+o");
        assert(cmd7.getOptional() == "user123");
    }
    catch (std::exception &e)
    {
        assert(false);
    }

    std::vector<std::string> in8 = split("MODE #channel -o user123");
    try
    {
        Mode cmd8(in8);
        assert(cmd8.getTarget() == "channel");
        assert(cmd8.getMode() == "-o");
        assert(cmd8.getOptional() == "user123");
    }
    catch (std::exception &e)
    {
        assert(false);
    }
}

static void lastTest()
{
    // Test setting and removing +l mode
    std::vector<std::string> in1 = split("MODE #channel +l");
    try
    {
        Mode cmd1(in1);
        assert(cmd1.getTarget() == "channel");
        assert(cmd1.getMode() == "+l");
        assert(cmd1.getOptional().empty());
    }
    catch (std::exception &e)
    {
        assert(false);
    }

    // Test setting and removing -l mode
    std::vector<std::string> in2 = split("MODE #channel -l");
    try
    {
        Mode cmd2(in2);
        assert(cmd2.getTarget() == "channel");
        assert(cmd2.getMode() == "-l");
        assert(cmd2.getOptional().empty());
    }
    catch (std::exception &e)
    {
        assert(false);
    }
	std::vector<std::string> in3 = split("MODE #channel +o user 12345");
    try
    {
        Mode cmd2(in3);
        assert(false);
    }
    catch (std::exception &e) {}
}

void test_Mode()
{
    testOnlyCmd();
    testCmdAndTargetAndMode();
    lastTest();
}
