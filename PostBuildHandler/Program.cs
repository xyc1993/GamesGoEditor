namespace PostBuildHandler
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            if (args.Length != 2)
            {
                Console.Error.WriteLine("PostBuildHandler.exe expects following arguments: <Source> <Target>");
                return;
            }

            string source = args[0];
            string target = args[1];

            Console.WriteLine($"PostBuildHandler::Source = {source}");
            Console.WriteLine($"PostBuildHandler::Target = {target}");

            string includeDirectory = Path.Combine(target, "Include");
            ClearDirectory(includeDirectory);
            CopyPublicHeaders(source, includeDirectory);

            Console.WriteLine($"PostBuildHandler::Finished all post build operations");
        }

        private static void ClearDirectory(string path)
        {
            Console.WriteLine($"PostBuildHandler::Clearing path = {path}");
            if (Directory.Exists(path))
            {
                Directory.Delete(path, recursive: true);
            }
            Directory.CreateDirectory(path);
        }

        private static bool CopyPublicHeaders(string source, string target)
        {
            bool hasHeaders = false;

            foreach (string file in Directory.GetFiles(source))
            {
                if (Path.GetExtension(file).Equals(".h", StringComparison.OrdinalIgnoreCase))
                {
                    if (!hasHeaders)
                    {
                        Directory.CreateDirectory(target);
                        hasHeaders = true;
                    }

                    string fileName = Path.GetFileName(file);
                    string destination = Path.Combine(target, fileName);
                    Console.WriteLine($"PostBuildHandler::Copying header from {file} to {destination}");
                    File.Copy(file, destination, true);
                }
            }

            foreach (string directory in Directory.GetDirectories(source))
            {
                string directoryName = Path.GetFileName(directory);
                string targetDirectory = Path.Combine(target, directoryName);
                if (CopyPublicHeaders(directory, targetDirectory))
                {
                    hasHeaders = true;
                }
            }

            return hasHeaders;
        }
    }
}