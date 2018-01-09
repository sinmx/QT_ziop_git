
using Dottest.Framework;
using Dottest.Framework.RecordState;
using NUnit.Framework;
using OPCTrendLib;

namespace DotTest.OPCTrendLib
{
    [TestFixture()]
    public class BitwiseOrTests
    {
        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestDoEval01()
        {
            BitwiseOr bitOr = new BitwiseOr();
            Accessor bitOrAccessor = ReflectionAccessor.Wrap(bitOr);
            Result[] argArray = new Result[2];
            Result res1 = new Result(2);
            Result res2 = new Result(1);
            argArray[0] = res1;
            argArray[1] = res2;
            bitOrAccessor.Call("DoEval", new Evaluator(), argArray);
        }

    }
}