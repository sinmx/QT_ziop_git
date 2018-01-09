using Dottest.Framework;
using NUnit.Framework;
using OPCTrendLib;

namespace DotTest.Factories.OPCTrendLib
{
    [TestFixture(), ObjectFactoryType()]
    public class IExecutorFactory
    {
        [ObjectFactoryMethod]
        [HashCode("/6vVng", "/tt8pQ")]
        public static IExecutor CreateIExecutor01()
        {
            IExecutor executor = new BooleanOrExecutor();
            return executor;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateIExecutor01()
        {
            IExecutor executor = CreateIExecutor01();
            Assert.IsNotNull(executor);
        }

        [ObjectFactoryMethod]
        [HashCode("/6vVng", "+pcZqg")]
        public static IExecutor CreateIExecutor02()
        {
            IExecutor executor = new Executor();
            return executor;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateIExecutor02()
        {
            IExecutor executor = CreateIExecutor02();
            Assert.IsNotNull(executor);
        }

        [ObjectFactoryMethod]
        [HashCode("/6vVng", "+NLaxA")]
        public static IExecutor CreateIExecutor03()
        {
            IExecutor executor = new BinaryOpExecutor();
            return executor;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateIExecutor03()
        {
            IExecutor executor = CreateIExecutor03();
            Assert.IsNotNull(executor);
        }

    }
}